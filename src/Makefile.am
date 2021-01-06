###### Determine where to load data files from
if conditional_use_project_datadir
datadir_path = $(srcdir)/../data
else
datadir_path = $(pkgdatadir)
endif

# These might be a good idea
# .POSIX:
AM_CFLAGS = \
	-std=c99 \
	-pedantic \
	-D_POSIX_C_SOURCE=200809L \
	-Wall \
	-Wextra \
	-DDATADIR=\"$(datadir_path)\"

AM_LDFLAGS = 

# This might be how to link against things:
# AM_CFLAGS += -lsome_library
# AM_LDFLAGS += -lsome_library

AM_CFLAGS += -pthread
AM_LDFLAGS += -lpthread

bin_PROGRAMS = some-glade-thing3
some_glade_thing3_SOURCES = main.c

# Examples for compiling against things
some_glade_thing3_CFLAGS = $(AM_CFLAGS) $(GTK_CFLAGS) -rdynamic
some_glade_thing3_LDFLAGS = $(AM_LDFLAGS) $(GTK_LIBS) 

# This might be how to add CPP stuff
# AM_CPPFLAGS =  -pedantic -Wall -Wextra
# AM_CPPFLAGS+= -std=c++11



