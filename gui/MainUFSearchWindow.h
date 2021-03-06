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

#ifndef NN_MAINUFSEARCHWINDOW_H
#define NN_MAINUFSEARCHWINDOW_H

#include <QtGui>
#include "../parse/parserFull.h"
#include "../eqnsearch/searchMaxMin.h"
#include "../eqnsearch/generateProof.h"
#include "../eqnsearch/isoSimpMetric.h"
#include "../eqnsearch/unchainMetric.h"
#include "../eqnsearch/numDownMetric.h"

class MainUFSearchWindow : public QWidget
{
	Q_OBJECT

	protected:
	std::string preproof;
	bool searchinit;
	searchMaxMin *engine;
	eqnMetric *rate;
	eqnMetric simp;
	unchainMetric unchain;
	numDownMetric numdown;
	int proofwidth;
	int proofheight;
	std::vector<eqnNode*> bList;

	void unlockButtons(bool input);

	public:
	MainUFSearchWindow();

	private slots:
	void fromHere();
	void newMoreWindow();
	void loadCurrentProof();
	void fillBest();
	void loadeqn();
	void loadProof(const QModelIndex &i);
	void deeper();
	void quit();

	public slots:
	void closeMoreWindow();
	void addToBest(const QModelIndex &i);

	private:
	QWidget *morewindow;
	QGridLayout *cols;
	
	QTextEdit *proofBox;
	QLineEdit *entry1;
	QLineEdit *entry2;

	QListView *list;
	QStandardItemModel *bestmodel;

	QPushButton *searchdeepbutton;
	QPushButton *closebutton;
	QPushButton *gobutton;
	QPushButton *morebutton;
	QPushButton *herebutton;
	QCheckBox *nicecheck;
};


#endif
