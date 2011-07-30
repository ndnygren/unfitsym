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
#include <sstream>

using namespace std;

void MainUFSearchWindow::fillBest()
{
	unsigned int i;

	bList.clear();
	bList = engine->best();
	bestmodel->clear();

	for (i = 0; i < bList.size(); i++)
	{
		bestmodel->appendRow(new QStandardItem(QString(bList[i]->str().c_str())));
//		if (i == 0) { entry2.set_active_text(bList[i]->str()); }
	}
}

void MainUFSearchWindow::loadeqn()
{
	parserFull parser;
	eqnNode *output;

	if (searchinit) 
	{
		delete engine; 
		delete rate;
		searchinit = false;
		proofBox->clear();
	}
	
	output = parser.getExpr(entry1->text().toStdString());

	if (output != 0)
	{
		rate = new isoSimpMetric(entry2->text().toStdString());
		engine = new searchMaxMin(output,rate);
		delete output;
		searchinit = true;
		fillBest();
	} 
	else
	{
		bestmodel->clear();
	}
}

void MainUFSearchWindow::loadProof(const QModelIndex &i)
{
	std::string temp = generateProof::build( engine->adjPairs, 
		engine->start->str(), 
		bList[i.row()]->str());
	proofBox->setPlainText(QString(temp.c_str()));
}

void MainUFSearchWindow::deeper()
{
	std::stringstream sstemp;
	proofBox->clear();
		

	if (searchinit)
	{
		engine->next(engine->exprMap.size());
		sstemp << "Stack size: "; 
		sstemp << (int)(engine->stack.size());
		sstemp << "\nMap size: ";
		sstemp << (int)(engine->exprMap.size());
		fillBest();
		proofBox->setPlainText(QString(sstemp.str().c_str()));
	}
}
 
void MainUFSearchWindow::quit()
{
	qApp->quit();
}

MainUFSearchWindow::MainUFSearchWindow()
{
	searchinit = false;
	cols = new QGridLayout();

	entry1 = new QLineEdit();
	entry1->setMinimumWidth(150);
	entry2 = new QLineEdit();
	entry2->setMaximumWidth(40);
	proofBox = new QTextEdit();
	proofBox->setMinimumWidth(450);

	list = new QListView();
	list->setMaximumWidth(300);
	bestmodel = new QStandardItemModel();
	list->setModel(bestmodel);

	searchdeepbutton = new QPushButton("Search Deeper");
	closebutton = new QPushButton("Close");
	closebutton->setMaximumWidth(50);
	gobutton = new QPushButton("Go");
	gobutton->setMaximumWidth(40);

	connect(closebutton, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(gobutton, SIGNAL(clicked()), this, SLOT(loadeqn()));
	connect(searchdeepbutton, SIGNAL(clicked()), this, SLOT(deeper()));
	connect(list, SIGNAL(clicked(const QModelIndex &)), this, SLOT(loadProof(const QModelIndex &)));

	cols->addWidget(entry1,0,0);
	cols->addWidget(entry2,0,1);
	cols->addWidget(gobutton,0,2);
	cols->addWidget(list,1,0,1,3);
	cols->addWidget(searchdeepbutton,2,2);
	cols->addWidget(proofBox,1,3,1,2);
	cols->addWidget(closebutton,2,4);

	setLayout(cols);
}

