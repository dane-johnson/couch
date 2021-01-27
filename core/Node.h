/**
   @file
   @author Dane Johnson <dane@danejohnson.org>
 
   @section LICENSE
 
   Couch  Copyright (C) 2021 Dane Johnson

   This program comes with ABSOLUTELY NO WARRANTY; without event the
   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for details at
   https://www.gnu.org/licenses/gpl-3.0.html
  
   This is free software, and you are welcome to redistribute it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.
 
   @section DESCRIPTION
 
   Node is the parent class for all classes that would be in the scene
   tree. The root of the scene tree is always a node.
*/

#ifndef NODE_H
#define NODE_H

#include <vector>

#include "types.h"

class Node; // Forwards declare
/**
   A list of nodes, tagged as either a list of prefabs
   or a list of instanced nodes.
*/
class NodeList : public std::vector<Node*> {
public:
  /**
     Add a node to this list, will check if it is a prefab 
     or an instance.
     @param node The node to add
  */
  void Append(Node *node);
  /**
     Whether or not this is a list of prefabs
     @returns true if this is a prefab list,
     false if it is an instanced list.
  */
  bool IsPrefabList();
private:
  bool isPrefabList = true;
  friend class Node;
};

/**
   The parent class for any object that will go into the scene tree
*/
class Node {
public:
  virtual Name GetType() const;

  /**
     Whether or not this object is a prefab, that is, if it is 
     an object being set up to be instanced one or more times.
     The alternative to being a prefab is being instanced, in which
     case it will be drawn, added to the physics system, etc.
     @return true if the object is a prefab, false if it is instanced.
  */
  bool IsPrefab();
  /**
     Returns the children of this node
     @return The list of children
  */
  NodeList GetChildren();
  /**
     Adds a node to this nodes list of children
     @param child The node to add
  */
  void AddChild(Node *child);
  
  /**
     Gets the root of the game scene tree
     @return The root node
  */
  static Node *GetRoot();
  /** 
      Allocates a new "default" version of this node.
      @return A reference to the node.
  */
  
  virtual Node* Create();
  /** 
      Copies the properties of this node to a newly allocated node, 
      created via @ref Create. Subclasses should override this to copy
      additional class attributes
      @return A reference to the duplicate
  */
  virtual Node* Duplicate();
  /**
     Creates an instanced version of this node, by calling @ref Duplicate.
     Subclasses should override this to perform neccesary tasks for
     instantiation, i.e. adding a physic object to the physics world.
     Any children of this node will also be instanced.
     @return an instanced version of this node.
  */
  virtual Node* Instance();

private:
  NodeList children;
  static Node *root;
  bool isPrefab = true;
  friend class NodeList;
};

#endif /* NODE_H */
