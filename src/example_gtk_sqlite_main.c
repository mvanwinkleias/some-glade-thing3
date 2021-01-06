/*

# ATTRIBUTION

This code is from here:

* https://stackoverflow.com/questions/45389291/how-to-display-data-from-a-sqlite-database-into-a-gtk-treeview
* https://stackoverflow.com/a/45390959

It was written by:
* José Fonte
* https://stackoverflow.com/users/7728864/jos%c3%a9-fonte

It has been modified to eliminate warnings on compile (vbox -> box).

# FUNCTIONALITY

It uses GTK to display a window containing data from an SQLite database.

# PURPOSE

It is included in this as an example to show how to compile against multiple
libraries.

# USE

* uncomment the PKG_CHECK_MODULES(... lines in configure.ac
* uncomment the some_glade_thing3_CFLAGS line in src/Makefile.am
* uncomment the some_glade_thing3_LDADD line in src/Makefile.am

Name this file "main.c", or configure src/Makefile.am to compile this

*/

#include <sqlite3.h>
#include <gtk/gtk.h>
#include <stdio.h>

int callback(void *, int, char **, char **);

enum {
	LIST_ID,
	LIST_BRAND,
	LIST_PRICE,
	N_COLUMNS
};


int main(int argc, char** argv) {
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkListStore *store; 
	GtkWidget *window;
	GtkWidget *list;

	GtkWidget *box;
	GtkWidget *label;
	GtkTreeSelection *selection;

	gtk_init(&argc, &argv);


	// THIS IS THE MODEL: 3 Columns of Type String

	store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

	// CREATE A SQLITE FILE WITH TABLE CARS AND POPULATE WITH DATA

	sqlite3 *db;
	char *err_msg = 0;

	int rc = sqlite3_open("test.db", &db);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "Cannot open database: %s\n", 
			   sqlite3_errmsg(db));
		sqlite3_close(db);

		return 1;
	}

	char *sql = "DROP TABLE IF EXISTS Cars;" 
		"CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
		"INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
		"INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
		"INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
		"INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
		"INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
		"INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
		"INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
		"INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	sql = "SELECT * FROM Cars";

	rc = sqlite3_exec(db, sql, callback, store, &err_msg);

	if (rc != SQLITE_OK ) {

		fprintf(stderr, "Failed to select data\n");
		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);
		sqlite3_close(db);

		return 1;
	} 

	sqlite3_close(db);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	list = gtk_tree_view_new();

	// CREATE 3 COLUMNS WITH TEXT CELL RENDERERS

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("ID",
		  renderer, "text", LIST_ID, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("BRAND",
		  renderer, "text", LIST_BRAND, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

	renderer = gtk_cell_renderer_text_new ();
	column = gtk_tree_view_column_new_with_attributes("PRICE",
		renderer, "text", LIST_PRICE, NULL);
	gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);


	// SET THE TREE VIEW MODEL 
	gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

	// TREEVIEW WILL KEEP A REFERENCE SO DECREASE REFCOUNT
	g_object_unref(store);

	// SETUP THE UI
	gtk_window_set_title(GTK_WINDOW(window), "List view");
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	gtk_window_set_default_size(GTK_WINDOW(window), 270, 250);

	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

	box = gtk_box_new(FALSE, 0);

	gtk_box_pack_start(GTK_BOX(box), list, TRUE, TRUE, 5);

	label = gtk_label_new("");
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);

	gtk_container_add(GTK_CONTAINER(window), box);

	g_signal_connect(G_OBJECT (window), "destroy",
	  G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;
}

/* From post comments

The most important part is the sqlite3 callback which takes the
GtkTreeModel/GtkListStore as first argument which then is filled with data, aka
populated.

The model is then set as the treeview model and the treeview will show the query
data

*/

int callback(void *model, int argc, char **argv, char **azColName) {
	GtkTreeIter iter;

	for (int i = 0; i < argc; i++) {

		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	}

	printf("\n");

	// AFTER PRINTING TO CONSOLE FILL THE MODEL WITH THE DATA

	gtk_list_store_append (GTK_LIST_STORE(model), &iter);
	gtk_list_store_set (GTK_LIST_STORE(model), &iter, LIST_ID, argv[0],
		LIST_BRAND, argv[1],
		LIST_PRICE, argv[2],
		-1
	);

	return 0;
}
