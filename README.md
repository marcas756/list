# list
Circular doubly linked list, Circular singly linked list

## linked list
In computer science, a linked list is a linear collection of data elements,
whose order is not given by their physical placement in memory.
Instead, each element points to the next. It is a data structure consisting
of a collection of nodes which together represent a sequence. In its most basic form,
each node contains: data, and a reference (in other words, a link) to the next node
in the sequence. This structure allows for efficient insertion or removal of elements
from any position in the sequence during iteration.
[https://en.wikipedia.org/wiki/Linked_list]

## singly linked list

Singly linked lists contain nodes which have a data field as well as 'next' field,
which points to the next node in line of nodes. Operations that can be performed on
singly linked lists include insertion, deletion and traversal.
[https://en.wikipedia.org/wiki/Linked_list#Singly_linked_list]

## doubly linked list

In a 'doubly linked list', each node contains, besides the next-node link, a second link field
pointing to the 'previous' node in the sequence. The two links may be called 'forward('s') and
'backwards', or 'next' and 'prev'('previous').
[https://en.wikipedia.org/wiki/Linked_list#Doubly_linked_list]


## circularly linked list

In the last node of a list, the link field often contains a null reference, a
special value is used to indicate the lack of further nodes. A less common convention
is to make it point to the first node of the list; in that case, the list is said to
be 'circular' or 'circularly linked'; otherwise, it is said to be 'open' or 'linear'.
It is a list where the last pointer points to the first node.
[https://en.wikipedia.org/wiki/Linked_list#Circular_linked_list]
