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
#include "model/PropertyModel.h"
#include "items/PropertyItem.h"
#include <QDebug>

PropertyModel::PropertyModel( QObject * parent  )
        :QAbstractItemModel(parent)
        ,_root(new PropertyItem("__ROOT"))
{
    _root->setVisible(false);
}


int PropertyModel::columnCount ( const QModelIndex & parent  ) const
{
    if (!parent.isValid())
        return _root->columnCount();
    PropertyItem *item = static_cast<PropertyItem*>(parent.internalPointer());
    if(item)
        return item->columnCount();
    return _root->columnCount();
}

QVariant PropertyModel::data ( const QModelIndex & index, int role) const
{
    if(!index.isValid())
        return QVariant();
    PropertyItem *item = static_cast<PropertyItem*>(index.internalPointer());
    if(!item)
        return QVariant();

    if(role==Qt::DisplayRole)
    {
        if(index.column()==0)
            return item->name();
        return item->data(PropertyItem::valueToRender);
    }
    return item->data(role);

}

bool PropertyModel::setData ( const QModelIndex & index, const QVariant & value, int role  )
{
    if(!index.isValid())
        return false;
    PropertyItem *item = static_cast<PropertyItem*>(index.internalPointer());
    if(!item)
        return false;
if(role==Qt::EditRole)
    role=PropertyItem::valueRole;

    item->setData( role,value);
    if(role==PropertyItem::valueRole)
    {
        qDebug()<<"EMIT";
        emit dataChanged(index,index);
    }
    return true;
}

QModelIndex PropertyModel::index ( int row, int column, const QModelIndex & parent) const
{
    PropertyItem *parentItem;
    if (!parent.isValid())
        parentItem = _root;
    else
        parentItem = static_cast<PropertyItem*>(parent.internalPointer());
    if(parentItem==NULL)
        return QModelIndex();
    PropertyItem *childItem = parentItem->childAt(row);
    if(childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();

}



QModelIndex PropertyModel::parent ( const QModelIndex & index ) const
{
    if(!index.isValid())
        return QModelIndex();
    PropertyItem *item=static_cast<PropertyItem *>(index.internalPointer());
    if(item==NULL)
        return QModelIndex();
    if(item->isRoot())
        return QModelIndex();
    PropertyItem *parentItem=item->parentInTree();
    if(parentItem==_root)
        return QModelIndex();
    if(parentItem==NULL)
        return QModelIndex();
    return createIndex(parentItem->index(),0, parentItem);
}

int PropertyModel::rowCount ( const QModelIndex & parent  ) const
{
    if(!parent.isValid())
        return _root->childCount();
    PropertyItem *item=static_cast<PropertyItem *>(parent.internalPointer());
    if(item==NULL)
        return _root->childCount();
    return item->childCount();
}

Qt::ItemFlags PropertyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    if(index.column()==0)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    PropertyItem *item=static_cast<PropertyItem *>(index.internalPointer());
    if(item==NULL)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    Qt::ItemFlags flg=0;
    if(item->isValid())
        flg|=Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    if(!item->isReadonly())
        flg|=Qt::ItemIsEditable;
    return flg;
}

QVariant PropertyModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return QVariant("_");

    return QVariant();
}



PropertyItem* PropertyModel::add
    (PropertyItem* item)
{
    if(!item)
        return item;
    item->reparent(_root);
    return item;
}


