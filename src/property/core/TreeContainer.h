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
#ifndef TREECONTAINER_H
#define TREECONTAINER_H

template <typename T>
class TreeContainer {
  protected:
    T *_treeParent;
    QList<T*>_treeChild;
  public:
    TreeContainer( T * parent = 0 );
    T* parent() const;
    void reparent( T * );
    void addChild( T * );
    void removeChild( T* );
    void removeChild( int );
    int childCount() const;
    T*childAt( int ) const;
    T*nextSibling();
    T*prevSibling();
    int indexOfChild( T * ) const;
    int index();
    bool isRoot() const;
    bool isLeaf() const;
    bool hasNextSibling();
    bool hasPrevSibling();
  };

template <typename T>
TreeContainer<T>::TreeContainer( T * parent )
    : _treeParent( 0 )
, _treeChild() {
  if ( parent )
    reparent( parent );
  }

template <typename T>
T* TreeContainer<T>::parent() const {
  return _treeParent;
  }

template <typename T>
void TreeContainer<T>::reparent( T *parent ) {
  if ( _treeParent )
    _treeParent->removeChild( static_cast<T*>( this ) );
  _treeParent = parent;
  if ( !_treeParent )
    return ;
  _treeParent->addChild( static_cast<T*>( this ) );
  }

template <typename T>
void TreeContainer<T>::addChild( T *child ) {
  if ( _treeChild.contains( child ) )
    return ;
  _treeChild.append( child );
  }

template <typename T>
void TreeContainer<T>::removeChild( T *child ) {
  _treeChild.removeAll( child );

  }

template <typename T>
void TreeContainer<T>::removeChild( int index ) {
  if ( index >= 0 && index < _treeChild.size() )
    _treeChild.removeAt( index );
  }

template <typename T>
int TreeContainer<T>::childCount() const {
  return _treeChild.size();
  }

template <typename T>
T* TreeContainer<T>::childAt( int index ) const {
  if ( index >= 0 && index < _treeChild.size() )
    return _treeChild.at( index );
  return 0;
  }

template <typename T>
T* TreeContainer<T>::nextSibling() {
  if ( _treeParent == 0 )
    return 0;
  return _treeParent->childAt( _treeParent->indexOfChild( this ) + 1 );
  }

template <typename T>
T* TreeContainer<T>::prevSibling() {
  if ( _treeParent == 0 )
    return 0;
  return _treeParent->childAt( _treeParent->indexOfChild( this ) - 1 );
  }

template <typename T>
int TreeContainer<T>::indexOfChild( T* child ) const {
  return _treeChild.indexOf( child );

  }

template <typename T>
int TreeContainer<T>::index() {
  if ( isRoot() )
    return 0;
  return _treeParent->indexOfChild( this );
  }

template <typename T>
bool TreeContainer<T>::isRoot() const {

  return _treeParent == 0;

  }

template <typename T>
bool TreeContainer<T>::isLeaf() const {
  return childCount() == 0;
  }

template <typename T>
bool TreeContainer<T>::hasNextSibling() {
  if ( _treeParent == 0 )
    return false;
  int idx = _treeParent->indexOfChild( this );
  if ( idx > -1 && ( idx + 1 ) >= _treeParent->childCount() )
    return false;
  return idx > -1;
  }

template <typename T>
bool TreeContainer<T>::hasPrevSibling() {
  if ( _treeParent == 0 )
    return false;
  int idx = _treeParent->indexOfChild( this );
  if ( idx > -1 && idx > 0 )
    return true;
  return false;

  }


#endif
