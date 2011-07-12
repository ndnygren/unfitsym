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
#include "eqnsearch/generateProof.h"

class ufForm
{
	protected:
	bool searchinit;
	searchMaxMin *engine;
	eqnMetric *rate;
	int proofwidth;
	int proofheight;
	vector<eqnNode*> bList;

	Gtk::Window window;
	Gtk::HBox columns, entrybox;
	Gtk::VBox col1, col2;
	Gtk::Button searchDeep, closeButton, goButton;
	Gtk::Entry exprentry,varentry;
	Gtk::ComboBoxText entry2;
	Gtk::TextView proofText;

	void fillBest()
	{
		unsigned int i;

		bList.clear();
		bList = engine->best();
		entry2.clear();

		for (i = 0; i < bList.size(); i++)
		{
			entry2.append_text(bList[i]->str());
			if (i == 0) { entry2.set_active_text(bList[i]->str()); }
		}
	}

	void loadeqn()
	{
		parserFull parser;
		eqnNode *output;

		if (searchinit) 
		{
			delete rate;
			delete engine; 
			searchinit = false;
		}
		
		output = parser.getExpr(exprentry.get_text());

		if (output != 0)
		{
			rate = new isoSimpMetric(varentry.get_text());
			engine = new searchMaxMin(output,rate);
			delete output;
			fillBest();
		}
	}

	void loadProof()
	{
		std::string temp = generateProof::build( engine->adjPairs, engine->start->str(), entry2.get_active_text());
		proofText.get_buffer()->set_text(temp);
	}

	void deeper() { engine->next(500); fillBest(); }
	void destroy() { gtk_main_quit (); }
	bool destroy1(GdkEventAny* event) { destroy(); return false; }

	public:
	ufForm()
	{
		proofwidth = 300;
		proofheight = 300;
		searchinit = false;

		goButton.set_label("Go");
		closeButton.set_label("Close");
		searchDeep.set_label("Search Deeper");
		varentry.set_text("x");
		proofText.set_size_request(proofwidth, proofheight);

		window.add(columns);
		col1.pack_start(entrybox,Gtk::PACK_SHRINK);
		entrybox.pack_start(exprentry,Gtk::PACK_SHRINK);
		entrybox.pack_start(varentry,Gtk::PACK_SHRINK);
		entrybox.pack_start(goButton,Gtk::PACK_SHRINK);
		col1.pack_start(entry2,Gtk::PACK_SHRINK);
		col1.pack_start(searchDeep,Gtk::PACK_SHRINK);
		col2.pack_start(proofText);
		col2.pack_start(closeButton,Gtk::PACK_SHRINK);
		columns.pack_start(col1,Gtk::PACK_SHRINK);
		columns.pack_start(col2);
	 
		window.set_title("unfitsym");

		closeButton.signal_clicked().connect(sigc::mem_fun(*this, &ufForm::destroy));
		goButton.signal_clicked().connect(sigc::mem_fun(*this, &ufForm::loadeqn));
		searchDeep.signal_clicked().connect(sigc::mem_fun(*this, &ufForm::deeper));
		entry2.signal_changed().connect(sigc::mem_fun(*this, &ufForm::loadProof));
		window.signal_delete_event().connect(sigc::mem_fun(*this, &ufForm::destroy1));

		window.show_all_children();

		Gtk::Main::run(window);
	}
};
