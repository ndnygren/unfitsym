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

#ifndef NN_UFMOREWINDOW_H
#define NN_UFMOREWINDOW_H

#include <QtGui>
#include "MainUFSearchWindow.h"
#include "../parse/parserFull.h"
#include "../eqnsearch/searchMaxMin.h"
#include "../eqnsearch/generateProof.h"
#include "../eqnsearch/isoSimpMetric.h"
#include "../eqnsearch/unchainMetric.h"
#include "../eqnsearch/numDownMetric.h"

class UFMoreWindow : public QWidget
{
	Q_OBJECT

	public:
	UFMoreWindow(MainUFSearchWindow* parent);
	void addNewLine(const std::string& input);

	private slots:
	void pushLine();

	private:
	MainUFSearchWindow *mainwindow;
	QGridLayout *cols;
	
	QStandardItemModel *bestmodel;
	QListView *list;

	QPushButton *addbutton;
	QPushButton *closebutton;
	
	protected:
	virtual void closeEvent(QCloseEvent *event);
};


#endif
