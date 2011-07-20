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

#include "MainUFSearchWindow.h"


MainUFSearchWindow::MainUFSearchWindow()
{
	cols = new QGridLayout();

	entry1 = new QLineEdit();
	entry2 = new QLineEdit();
	proofBox = new QTextEdit();

	list = new QListView();

	searchdeepbutton = new QPushButton("Search Deeper");
	closebutton = new QPushButton("Close");
	closebutton->setMaximumWidth(50);
	gobutton = new QPushButton("Go");
	gobutton->setMaximumWidth(40);

	cols->addWidget(entry1,0,0);
	cols->addWidget(entry2,0,1);
	cols->addWidget(gobutton,0,2);
	cols->addWidget(list,1,0,1,3);
	cols->addWidget(searchdeepbutton,2,2);
	cols->addWidget(proofBox,1,3,1,2);
	cols->addWidget(closebutton,2,4);

	setLayout(cols);
}

