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
#ifndef ABSTRACTPLUGINSFACTORY_H
#define ABSTRACTPLUGINSFACTORY_H

#include <QObject>
#include <QStringList>
#include <QDir>
#include <QPluginLoader>
#include <QHash>
#include <QtDebug>


template <typename T>
class Singleton {
  protected:
    static T *_instance;
    Singleton();
  public:
    static T& instance();
  };

template <typename T>
T* Singleton<T>::_instance = 0;

template <typename T>
Singleton<T>::Singleton() {}

template <typename T>
T& Singleton<T>::instance() {
  if ( _instance == NULL )
    _instance = new T();
  return *_instance;
  }


class AbstractItemBuilder {
  public:
    AbstractItemBuilder() {};
    virtual ~AbstractItemBuilder() {};
    virtual void* instance() = 0;
    virtual AbstractItemBuilder* newOneOfThis() = 0;
  };

template <class T>
class GenericItemBuilder : public AbstractItemBuilder {
  public:
    GenericItemBuilder();
    virtual ~GenericItemBuilder();
    void* instance() {
      return new T();
      };
    virtual AbstractItemBuilder* newOneOfThis() {
      return new GenericItemBuilder<T>();
      };
  };


template <typename T>
GenericItemBuilder<T>::GenericItemBuilder() {}
template <typename T>
GenericItemBuilder<T>::~GenericItemBuilder() {}


template <class T>
class GenericSingletonItemBuilder : public AbstractItemBuilder {
    T *_instance;
  public:
    GenericSingletonItemBuilder();
    virtual ~GenericSingletonItemBuilder();
    void* instance() {
      if ( !_instance )
        _instance = new T();
      return _instance;
      };
    virtual AbstractItemBuilder* newOneOfThis() {
      return new GenericSingletonItemBuilder<T>();
      };

  };


template <typename T>
GenericSingletonItemBuilder<T>::GenericSingletonItemBuilder()
    : AbstractItemBuilder()
, _instance( NULL ) {}
template <typename T>
GenericSingletonItemBuilder<T>::~GenericSingletonItemBuilder() {}



template <typename K = QString>
class Factory {
    QHash <K, AbstractItemBuilder*>_hash;
  public:
    Factory();
    int loadPlugins( const QString &pluginsPath, const QString &pluginsPattern = "*" );
    template <class U>
    void add( const K&id, bool useSingletonBuider = false );
    void add( const K&id, AbstractItemBuilder* );
    void removeAll( bool autodeleteBuilder = true );
    void remove ( const K&id, bool autodeleteBuilder = true );
    int count() const;
    template <typename U>
    U* getAtIndex( int i ) const;
    AbstractItemBuilder* getBuilderAtIndex( int i ) const;
    const K& keyAtIndex( int i ) const;
    template <typename U>
    U* get ( const K&id ) const;
    AbstractItemBuilder* getBuilder( const K&id ) const;
    void merge( const Factory<>*other, bool keepMyBuilder = true, bool autodeleteBuilder = true );
    Factory<K> getACopy( bool useSameReferenceOnBuilder = false );

  };




template <typename K>
Factory<K>::Factory()
  : _hash() {}


template <typename K>
int Factory<K>::loadPlugins( const QString &pluginsPath, const QString &pluginsPattern ) {
#if 0 //pas utilise pour l'instant
  QDir plgDir = QDir( pluginsPath, pluginsPattern, QDir::Name, QDir::Files );
  int count = 0;
  foreach ( QString fileName, plgDir.entryList( QDir::Files ) ) {
    QPluginLoader loader( plgDir.absoluteFilePath( fileName ) );
    QObject *plugin = loader.instance();
    if ( !plugin )
      continue; //<- ce serait sympa de prevenir que ca a plante
    interface::FactoryInterface*iface = qobject_cast<interface::FactoryInterface*>( plugin );
    if ( iface == NULL ) {
      loader.unload();
      continue; //<- ce serait sympa de prevenir que ca a plante
      }
    _hash[ iface->Id() ] = iface->builder();
    count++;
    }
  return count;
#else

  return 0;
#endif

  }


template <typename K>
template <class U>
void Factory<K>::add
  ( const K&id, bool unique ) {
  AbstractItemBuilder * builder = NULL;
  if ( !unique )
    builder = new GenericItemBuilder<U>();
  else
    builder = new GenericSingletonItemBuilder<U>();
  add
    ( id, builder );
  }

template <typename K>
void Factory<K>::add
  ( const K&id, AbstractItemBuilder*builder ) {
  _hash[ id ] = builder;
  }


template <typename K>
void Factory<K>::removeAll( bool autodeleteBuilder) {
 //TODO gere le autodeleteBuilder
        _hash.clear();
  }

template <typename K>
void Factory<K>::remove
  ( const K&id, bool autodeleteBuilder ) {
  _hash.remove( id );
  }

template <typename K>
int Factory<K>::count() const {
  return _hash.size();
  }


template <typename K>
template <typename U>
U* Factory<K>::getAtIndex( int i ) const {
  AbstractItemBuilder * builder = getBuilderAtIndex( i );
  if ( !builder )
    return NULL;
  return static_cast<U*>( builder->instance() );
  }

template <typename K>
AbstractItemBuilder* Factory<K>::getBuilderAtIndex( int i ) const {
  if ( i < 0 || i >= _hash.size() )
    return NULL;
  return ( _hash.begin() + i ).value();
  }

template <typename K>
const K& Factory<K>::keyAtIndex( int i ) const {
  if ( i < 0 || i >= _hash.size() )
    return K();
  return ( _hash.begin() + i ).key();
  }

template <typename K>
template <typename U>
U* Factory<K>::get
  ( const K&id ) const {
    AbstractItemBuilder * builder = getBuilder( id );
    if ( !builder )
      return NULL;
    return static_cast<U*>( builder->instance() );
    }

template <typename K>
AbstractItemBuilder* Factory<K>::getBuilder( const K&id ) const {
  if ( !_hash.contains( id ) )
    return NULL;
  return ( _hash.find( id ) ).value();
  }


template <typename K>
void Factory<K>::merge( const Factory<>*other, bool keepMyBuilder, bool autodeleteBuilder ) {
  for ( int i = 0;i < other->count();i++ ) {
    if ( getBuilder( other->keyAtIndex( i )!="" && keepMyBuilder ) )
      continue;
    else
      remove
        ( other->keyAtIndex( i ), autodeleteBuilder );
    add
      ( other->keyAtIndex( i ), other->getBuilderAtIndex( i ) );
    }
  }

template <typename K>
Factory<K> Factory<K>::getACopy( bool useSameReferenceOnBuilder ) {

  Factory<K> cpy;
  for ( int i = 0;i < count();i++ ) {
    if ( getBuilderAtIndex( i ) ) {
      if ( !useSameReferenceOnBuilder )
        cpy.add( keyAtIndex( i ), getBuilderAtIndex( i ).newOneOfThis() );
      else
        cpy.add( keyAtIndex( i ), getBuilderAtIndex( i ) );

      } else
      cpy.add( keyAtIndex( i ), 0 );
    }
  return cpy;
  }

#endif
