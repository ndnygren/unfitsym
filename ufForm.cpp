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

#include <gtkmm.h>
#include "parse/parserFull.h"
#include "eqnsearch/searchMaxMin.cpp"
#include "eqnsearch/isoSimpMetric.h"

class ufForm
{
	protected:
	bool searchinit;
	searchMaxMin *engine;
	eqnMetric *rate;
	int proofwidth;
	int proofheight;

	Gtk::Window window;
	Gtk::HBox columns, entrybox;
	Gtk::VBox col1, col2;
	Gtk::Button searchDeep, closeButton, goButton;
	Gtk::Entry exprentry,varentry;
	Gtk::Combo entry2;
	Gtk::TextView proofText;

	void loadeqn()
	{
	    gtk_main_quit();
	}

	void destroy()
	{
	    gtk_main_quit ();
	}

	public:
	ufForm()
	{
		proofwidth = 300;
		proofheight = 300;
		searchinit = false;

		goButton.set_label("Go");
		closeButton.set_label("Close");
		searchDeep.set_label("Search Deeper");
		proofText.set_size_request(proofwidth, proofheight);

		window.add(columns);
		col1.pack_start(entrybox);
		entrybox.pack_start(exprentry);
		entrybox.pack_start(varentry);
		entrybox.pack_start(goButton);
		col1.pack_start(entry2);
		col1.pack_start(searchDeep);
		col2.pack_start(proofText);
		col2.pack_start(closeButton);
		columns.pack_start(col1);
		columns.pack_start(col2);
	 
		window.set_title("unfitsym");

//		closeButton.signal_clicked().connect(sigc::mem_fun(*this, &ufForm::destroy));
//		goButton.signal_clicked().connect(sigc::mem_fun(*this, &ufForm::destroy));
//		window.signal_delete_event().connect(sigc::mem_fun(*this, &ufForm::destroy));

		Gtk::Main::run(window);
	}
};
