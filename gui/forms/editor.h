//
// C++ Interface: editor
//
// Description: 
//
//
// Author: Marcus Dirks <marcus.dirks@web.de>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef EDITOR_H
#define EDITOR_H

/**
	@author Marcus Dirks <marcus.dirks@web.de>
*/
class Editor{
public:
    Editor();

    ~Editor();
    virtual void stopEdit() = 0;
    virtual void startEdit() = 0;

};

#endif
