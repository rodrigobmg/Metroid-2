#include "QNode.h"


QNode::QNode(void)
{
<<<<<<< HEAD
	posX = 0;
	posY = 0;
	width = 0;
	height = 0;
=======
	left = 0;
	top = 0;
	size = 0;
>>>>>>> 4d41ca4be8ebf3768d7d854b952cb4081057ddbb
	leftTop = NULL;
	rightBottom = NULL;
	leftBottom = NULL;
	rightTop = NULL;
}

QNode::QNode(int _left, int _top, int _size, list<int> _list)
{
<<<<<<< HEAD
	posX = _left;
	posY = _top;
	width = _width;
	height = _height;
=======
	left = _left;
	top = _top;
	size = _size;
>>>>>>> 4d41ca4be8ebf3768d7d854b952cb4081057ddbb
	leftTop = NULL;
	rightBottom = NULL;
	leftBottom = NULL;
	rightTop = NULL;
	listObject = _list;
}

void QNode::Insert(int key)
{
	listObject.push_back(key);
}

QNode::QNode(const QNode& _node)
{
<<<<<<< HEAD
	posX = _node.posX;
	posY = _node.posY;
	width = _node.width;
	height = _node.height;
=======
	left = _node.left;
	top = _node.top;
	size = _node.size;
>>>>>>> 4d41ca4be8ebf3768d7d854b952cb4081057ddbb
	leftTop = _node.leftTop;
	leftBottom = _node.leftBottom;
	rightTop = _node.rightTop;
	rightBottom = _node.rightBottom;
	listObject = _node.listObject;
}

QNode::~QNode(void)
{
}
