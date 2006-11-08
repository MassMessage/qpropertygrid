/***************************************************************************
 *   Copyright (C) 2006 by ludo   *
 *   ludo42fr@free.fr   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                         *
 *   In addition, as a special exception, the copyright holders give       *
 *   permission to link the code of this program with any edition of       *
 *   the Qt library by Trolltech AS, Norway (or with modified versions     *
 *   of Qt that use the same license as Qt), and distribute linked         *
 *   combinations including the two.  You must obey the GNU General        *
 *   Public License in all respects for all of the code used other than    *
 *   Qt.  If you modify this file, you may extend this exception to        *
 *   your version of the file, but you are not obligated to do so.  If     *
 *   you do not wish to do so, delete this exception statement from        *
 *   your version.                                                         *
 ***************************************************************************/
#include "mainform.h"
#include <QMouseEvent>
#include <QDebug>
#include "items/PropertyItem.h"
#include "items/PropertyItemFromQObject.h"
sampleForm::sampleForm()
:QMainWindow(0)
,Ui_MainWindow()
,_tree()
{
setupUi(this);
_tree.show();
connect(getPropButton,SIGNAL(clicked(bool)),this,SLOT(onSelectWidget(bool)));
}

void sampleForm::mouseReleaseEvent( QMouseEvent * event )
{
releaseMouse();
QWidget *w=childAt(event->pos());
if(!w)
{
  qDebug("Pas de widget");
return;
}
PropertyModel *model=new PropertyModel();
PropertyItemFromQObject *conv=new PropertyItemFromQObject(0);
PropertyItem *it=conv->importFrom(w,0);
model->add(it);
_tree.setModel(model);
_tree.show();

}


void sampleForm::onSelectWidget(bool)
{

grabMouse();
}