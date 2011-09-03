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

#include "UFMoreWindow.h"

using namespace std;

void UFMoreWindow::pushLine()
{
	mainwindow->addToBest(list->currentIndex());
}

void UFMoreWindow::addNewLine(const std::string& input)
{
	bestmodel->appendRow(new QStandardItem(QString(input.c_str())));	
}

UFMoreWindow::UFMoreWindow(MainUFSearchWindow *parent)
{
	mainwindow = parent;
	cols = new QGridLayout();
	
	list = new QListView();
	list->setMaximumWidth(350);
	bestmodel = new QStandardItemModel();
	list->setModel(bestmodel);

	addbutton = new QPushButton("Add");
	closebutton = new QPushButton("Close");
	addbutton->setMaximumWidth(50);
	closebutton->setMaximumWidth(50);

	connect(closebutton, SIGNAL(clicked()), mainwindow, SLOT(closeMoreWindow()));
	connect(addbutton, SIGNAL(clicked()), this, SLOT(pushLine()));

	cols->addWidget(list,0,0,1,3);
	cols->addWidget(addbutton,1,1);
	cols->addWidget(closebutton,1,2);

	setLayout(cols);
}

