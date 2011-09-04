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
#include "UFMoreWindow.h"
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

void MainUFSearchWindow::unlockButtons(bool input)
{
	herebutton->setEnabled(input);
	morebutton->setEnabled(input);
	searchdeepbutton->setEnabled(input);
}

void MainUFSearchWindow::newMoreWindow()
{
	unlockButtons(false);
	gobutton->setEnabled(false);
	morewindow = new UFMoreWindow(this);
	morewindow->show();

	map<string, eqnNode*>::iterator it;

	for (it=engine->exprMap.begin(); it!=engine->exprMap.end(); it++)
	{
		((UFMoreWindow*)morewindow)->addNewLine((*it).first);
	}
}

void MainUFSearchWindow::fromHere()
{
	eqnNode *output;

	if (list->currentIndex().row() != -1)
	{
		if (nicecheck->isChecked())
		{
			preproof += generateProof::nice_build( engine->adjPairs, 
				engine->start->str(), 
				bList[list->currentIndex().row()]->str());
		}
		else 
		{
			preproof += generateProof::build( engine->adjPairs, 
				engine->start->str(), 
				bList[list->currentIndex().row()]->str());
		}

		delete engine; 
		delete rate;
		proofBox->clear();

		output = bList[list->currentIndex().row()];

		rate = new isoSimpMetric(entry2->text().toStdString());
		engine = new searchMaxMin(output,rate);
		fillBest();
	}
}

void MainUFSearchWindow::closeMoreWindow()
{
	morewindow->close();
	delete morewindow;
	unlockButtons(true);
	gobutton->setEnabled(true);
}

void MainUFSearchWindow::addToBest(const QModelIndex &i)
{
	eqnNode *output = parserFull::getExpr(i.data().toString().toStdString());
	if (output != 0)
	{
		bList.push_back(output);
		bestmodel->appendRow(new QStandardItem(QString(output->nice_str().c_str())));	
	}
}

void MainUFSearchWindow::fillBest()
{
	unsigned int i;

	bList.clear();
	bList = engine->best();
	bestmodel->clear();

	for (i = 0; i < bList.size(); i++)
	{
		bestmodel->appendRow(new QStandardItem(QString(bList[i]->nice_str().c_str())));
	}
}

void MainUFSearchWindow::loadeqn()
{
	eqnNode *output;
	
	preproof = "";

	if (searchinit) 
	{
		delete engine; 
		delete rate;
		searchinit = false;
		unlockButtons(false);
		proofBox->clear();
	}
	
	output = parserFull::getExpr(entry1->text().toStdString());

	if (output != 0)
	{
		rate = new isoSimpMetric(entry2->text().toStdString());
		engine = new searchMaxMin(output,rate);
		engine->addNewDirection(&simp);
		engine->addNewDirection(&unchain);
		engine->addNewDirection(&numdown);
		delete output;
		searchinit = true;
		unlockButtons(true);
		fillBest();
	} 
	else
	{
		bestmodel->clear();
	}
}

void MainUFSearchWindow::loadCurrentProof()
{
	if (list->currentIndex().row() != -1)
	{
		loadProof(list->currentIndex());
	}
}

void MainUFSearchWindow::loadProof( const QModelIndex &i)
{
	std::string temp;

	if (nicecheck->isChecked())
	{
		temp = generateProof::nice_build( engine->adjPairs, 
		engine->start->str(), 
		bList[i.row()]->str());
	}
	else
	{
		temp = generateProof::build( engine->adjPairs, 
		engine->start->str(), 
		bList[i.row()]->str());
	}
	proofBox->setPlainText(QString((preproof + temp).c_str()));
}

void MainUFSearchWindow::deeper()
{
	std::stringstream sstemp;
	proofBox->clear();
		

	if (searchinit)
	{
		engine->next(engine->exprMap.size());
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
	QLabel *inputlabel = new QLabel("Input:");
	QLabel *varlabel = new QLabel("Var:");
	QGroupBox *prooflabel = new QGroupBox("Proof");
	QGroupBox *sollabel = new QGroupBox("Possible Solutions");
	QHBoxLayout *inputlayout = new QHBoxLayout();
	QHBoxLayout *varlayout = new QHBoxLayout();
	QVBoxLayout *prooflayout = new QVBoxLayout();
	QVBoxLayout *sollayout = new QVBoxLayout();

	searchinit = false;
	cols = new QGridLayout();

	entry1 = new QLineEdit();
	entry1->setMinimumWidth(150);
	entry2 = new QLineEdit();
	entry2->setMaximumWidth(40);
	proofBox = new QTextEdit();
	proofBox->setMinimumWidth(380);

	list = new QListView();
	list->setMaximumWidth(350);
	bestmodel = new QStandardItemModel();
	list->setModel(bestmodel);

	searchdeepbutton = new QPushButton("Search Deeper");
	closebutton = new QPushButton("Close");
	closebutton->setMaximumWidth(50);
	gobutton = new QPushButton("Go");
	gobutton->setMaximumWidth(40);
	morebutton = new QPushButton("More");
	morebutton->setMaximumWidth(50);
	herebutton = new QPushButton("From Here");
	herebutton->setMaximumWidth(70);
	nicecheck = new QCheckBox("Nice Output");

	connect(closebutton, SIGNAL(clicked()), qApp, SLOT(quit()));
	connect(morebutton, SIGNAL(clicked()), this, SLOT(newMoreWindow()));
	connect(herebutton, SIGNAL(clicked()), this, SLOT(fromHere()));
	connect(gobutton, SIGNAL(clicked()), this, SLOT(loadeqn()));
	connect(searchdeepbutton, SIGNAL(clicked()), this, SLOT(deeper()));
	connect(list, SIGNAL(clicked(const QModelIndex &)), this, SLOT(loadProof(const QModelIndex &)));
	connect(nicecheck, SIGNAL(clicked()), this, SLOT(loadCurrentProof()));

	inputlayout->addWidget(inputlabel);
	inputlayout->addWidget(entry1);
	varlayout->addWidget(varlabel);
	varlayout->addWidget(entry2);
	prooflayout->addWidget(proofBox);
	prooflabel->setLayout(prooflayout);
	sollayout->addWidget(list);
	sollabel->setLayout(sollayout);

	cols->addLayout(inputlayout,0,0);
	cols->addLayout(varlayout,0,1);
	cols->addWidget(gobutton,0,2,1,1,Qt::AlignBottom);
	cols->addWidget(sollabel,1,0,1,3);
	cols->addWidget(searchdeepbutton,2,2);
	cols->addWidget(morebutton,2,1);
	cols->addWidget(herebutton,2,0);
	cols->addWidget(prooflabel,0,3,2,2);
	cols->addWidget(closebutton,2,4);
	cols->addWidget(nicecheck,2,3);

	preproof = "";

	unlockButtons(false);
	setLayout(cols);
}

