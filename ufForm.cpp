/* unfitsym - framework for symbolic computation
* Copyright (C) 2011 Nick Nygren
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>. */

#include <gtk/gtk.h>
#include "parse/parserFull.h"
#include "eqnsearch/searchMaxMin.cpp"
#include "eqnsearch/isoSimpMetric.h"

class ufForm
{
	protected:
	bool searchinit;
	searchMaxMin *engine;
	eqnMetric *rate;

	GtkWidget *window;
	GtkWidget *columns;
	GtkWidget *col1, *col2, *entrybox;
	GtkWidget *exprentry, *varentry, *entry2;
	GtkWidget *prooftext;
	GtkWidget *searchDeep, *closeButton, *goButton;
	GtkTextBuffer *proofBuffer;

	gint proofwidth;
	gint proofheight;

	void loadeqn(GtkWidget *widget, gpointer data )
	{
	    gtk_main_quit();
	}

	void destroy(GtkWidget *widget, gpointer data )
	{
	    gtk_main_quit ();
	}

	public:
	ufForm()
	{
		proofwidth = 300;
		proofheight = 300;
		searchinit = false;

		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		columns = gtk_hbox_new(FALSE, 0);
		entrybox = gtk_hbox_new(FALSE, 0);
		col1 = gtk_vbox_new(FALSE, 0);
		col2 = gtk_vbox_new(FALSE, 0);
		exprentry = gtk_entry_new();
		varentry = gtk_entry_new();
		entry2 = gtk_combo_new();
		prooftext = gtk_text_view_new_with_buffer(NULL);
		proofBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(prooftext));
		gtk_text_buffer_set_text(proofBuffer, " ",-1);
		gtk_widget_set_size_request(GTK_WIDGET(prooftext), proofwidth, proofheight);
		searchDeep = gtk_button_new_with_label ("Search Deeper");
		closeButton = gtk_button_new_with_label ("Close");
		goButton = gtk_button_new_with_label ("Go");

		gtk_container_add (GTK_CONTAINER (window), columns);
		gtk_box_pack_start(GTK_BOX(col1), entrybox, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(entrybox), exprentry, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(entrybox), varentry, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(entrybox), goButton, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(col1), entry2, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(col1), searchDeep, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(col2), prooftext, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(col2), closeButton, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(columns), col1, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(columns), col2, FALSE, FALSE, 0);
	 
		gtk_window_set_title (GTK_WINDOW (window), "unfitsym");

		g_signal_connect (window, "destroy", G_CALLBACK (destroy), NULL);
		g_signal_connect (closeButton, "clicked", G_CALLBACK (destroy), NULL);
		g_signal_connect (goButton, "clicked", G_CALLBACK (loadeqn), NULL);

		gtk_widget_show (exprentry);
		gtk_widget_show (varentry);
		gtk_widget_show (entry2);
		gtk_widget_show (closeButton);
		gtk_widget_show (goButton);
		gtk_widget_show (prooftext);
		gtk_widget_show (searchDeep);
		gtk_widget_show (entrybox);
		gtk_widget_show (col1);
		gtk_widget_show (col2);
		gtk_widget_show (columns);
		gtk_widget_show (window);

	}
};
