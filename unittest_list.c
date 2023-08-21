/*! \copyright
    Copyright (c) 2013, marco@bacchi.at
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:
    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
       notice, this list of conditions and the following disclaimer in the
       documentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to endorse or promote
       products derived from this software without specific prior
       written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
    OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
    GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*!
    \file   unittest_list.c

    \brief

    \details
*/




#include "unittest.h"
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>


#define UNITTEST_LIST_TYPE_SLIST 0
#define UNITTEST_LIST_TYPE_DLIST 1


#define UNITTEST_LIST_TYPE UNITTEST_LIST_TYPE_DLIST

#if ( UNITTEST_LIST_TYPE == UNITTEST_LIST_TYPE_SLIST )
    #include"unittest_slist.h"
#elif ( UNITTEST_LIST_TYPE == UNITTEST_LIST_TYPE_DLIST )
    #include"unittest_dlist.h"
#else
    #error "Unknown list type"
#endif


typedef struct {
    LIST_NODE_TYPE;
    int data;
}int_node_t;

int_node_t int_nodes[3]=
{
        {.data = 0},
        {.data = 1},
        {.data = 2}
};


UNITTEST_TESTCASE(init)
{
    list_t list = {0};

    list_init(&list);

    UNITTEST_ASSERT("Next item of list has to be list itself",list_next(&list,&list) == &list);
    UNITTEST_ASSERT("Previous item of list has to be list itself",list_prev(&list,&list) == &list);
    UNITTEST_ASSERT("List has to be empty",list_empty(&list));
    UNITTEST_ASSERT("An empty list has to contain 0 list elements",list_size(&list) == 0);


    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_front(&list,&int_nodes[idx]);
    }

    UNITTEST_ASSERT("Expected list not to be empty",!list_empty(&list));
    UNITTEST_ASSERT("Expected 3 nodes in list",list_size(&list) == 3);
    UNITTEST_ASSERT("Next node of list must not to be list itself",list_next(&list,&list) != &list);
    UNITTEST_ASSERT("Previous node of list must not be list itself",list_prev(&list,&list) != &list);

    list_init(&list);

    UNITTEST_ASSERT("Next item of list has to be list itself",list_next(&list,&list) == &list);
    UNITTEST_ASSERT("Previous item of list has to be list itself",list_prev(&list,&list) == &list);
    UNITTEST_ASSERT("List has to be empty",list_empty(&list));
    UNITTEST_ASSERT("An empty list has to contain 0 list elements",list_size(&list) == 0);
}


UNITTEST_TESTCASE(push_front)
{
    list_t list;

    list_init(&list);



    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_front(&list,&int_nodes[idx]);
        UNITTEST_ASSERT("Expected other front node", list_front(&list) == ((list_node_t*)&int_nodes[idx]) );
        UNITTEST_ASSERT("Expected front node with another int value", ((int_node_t*)list_front(&list))->data == int_nodes[idx].data  );
    }

    UNITTEST_ASSERT("List must not be empty",!list_empty(&list));
    UNITTEST_ASSERT("List has to contain 3 nodes",list_size(&list) == 3);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("node must be in list", list_find(&list,&int_nodes[idx]));
    }


    int_node_t int_node = {.data=3};
    UNITTEST_ASSERT("node must not be in list", !list_find(&list,&int_node));

    int_node_t  *iterator;
    int val = 2;

    list_foreach(&list,iterator)
    {
        UNITTEST_ASSERT("Issue with order of items in the list", iterator->data == val );
        val--;
    }

    UNITTEST_ASSERT("Back of list must be node with index 0", list_back(&list) == ((list_node_t*)&int_nodes[0]) );
    UNITTEST_ASSERT("Back of list must be node containing int value 0", ((int_node_t*)list_back(&list))->data == 0  );
    UNITTEST_ASSERT("Front of list must be node with index 2", list_front(&list) == ((list_node_t*)&int_nodes[2]) );
    UNITTEST_ASSERT("Front of list must be node containing int value 2", ((int_node_t*)list_front(&list))->data == 2  );

    UNITTEST_ASSERT("Middle of list must be node with index 1", list_prev(&list,list_back(&list)) == ((list_node_t*)&int_nodes[1]) );
    UNITTEST_ASSERT("Middle of list must be node with index 1", list_next(&list,list_front(&list)) == ((list_node_t*)&int_nodes[1]) );
    UNITTEST_ASSERT("Middle of list must be node containing int value 1", ((int_node_t*)list_next(&list,list_front(&list)))->data == 1  );
    UNITTEST_ASSERT("Middle of list must be node containing int value 1", ((int_node_t*)list_prev(&list,list_back(&list)))->data == 1  );

    UNITTEST_ASSERT("Front of list node must have list itself as predecessor", list_prev(&list,list_front(&list)) == &list);
}

UNITTEST_TESTCASE(push_back)
{
    list_t list;

    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_back(&list,&int_nodes[idx]);
        UNITTEST_ASSERT("Expected other back node", list_back(&list) == ((list_node_t*)&int_nodes[idx]) );
        UNITTEST_ASSERT("Expected back node with another int value", ((int_node_t*)list_back(&list))->data == int_nodes[idx].data  );
    }

    UNITTEST_ASSERT("List must not be empty",!list_empty(&list));
    UNITTEST_ASSERT("List has to contain 3 nodes",list_size(&list) == 3);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("node must be in list", list_find(&list,&int_nodes[idx]));
    }

    int_node_t int_node = {.data=3};
    UNITTEST_ASSERT("node must not be in list", !list_find(&list,&int_node));

    int_node_t  *iterator;
    int val = 0;

    list_foreach(&list,iterator)
    {
        UNITTEST_ASSERT("Issue with order of items in the list", iterator->data == val );
        val++;
    }

    UNITTEST_ASSERT("Back of list must be node with index 2", list_back(&list) == ((list_node_t*)&int_nodes[2]) );
    UNITTEST_ASSERT("Back of list must be node containing int value 2", ((int_node_t*)list_back(&list))->data == 2  );
    UNITTEST_ASSERT("Front of list must be node with index 0", list_front(&list) == ((list_node_t*)&int_nodes[0]) );
    UNITTEST_ASSERT("Front of list must be node containing int value 0", ((int_node_t*)list_front(&list))->data == 0  );

    UNITTEST_ASSERT("Middle of list must be node with index 1", list_prev(&list,list_back(&list)) == ((list_node_t*)&int_nodes[1]) );
    UNITTEST_ASSERT("Middle of list must be node with index 1", list_next(&list,list_front(&list)) == ((list_node_t*)&int_nodes[1]) );
    UNITTEST_ASSERT("Middle of list must be node containing int value 1", ((int_node_t*)list_next(&list,list_front(&list)))->data == 1  );
    UNITTEST_ASSERT("Middle of list must be node containing int value 1", ((int_node_t*)list_prev(&list,list_back(&list)))->data == 1  );

    UNITTEST_ASSERT("Back of list node must have list itself as successor", list_next(&list,list_back(&list)) == &list);
}


UNITTEST_TESTCASE(clear)
{
    list_t list = {0};

    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_front(&list,&int_nodes[idx]);
    }

    UNITTEST_ASSERT("Expected list not to be empty",!list_empty(&list));
    UNITTEST_ASSERT("Expected 3 nodes in list",list_size(&list) == 3);
    UNITTEST_ASSERT("Next node of list must not to be list itself",list_next(&list,&list) != &list);
    UNITTEST_ASSERT("Previous node of list must not be list itself",list_prev(&list,&list) != &list);

    list_clear(&list);

    UNITTEST_ASSERT("Next item of list has to be list itself",list_next(&list,&list) == &list);
    UNITTEST_ASSERT("Previous item of list has to be list itself",list_prev(&list,&list) == &list);
    UNITTEST_ASSERT("List has to be empty",list_empty(&list));
    UNITTEST_ASSERT("An empty list has to contain 0 list elements",list_size(&list) == 0);
}


UNITTEST_TESTCASE(size)
{
    list_t list = {0};
    list_init(&list);
    UNITTEST_ASSERT("Expected 0 nodes in list",list_size(&list) == 0);


    /* push front / pop back */

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx);
        list_push_front(&list,&int_nodes[idx]);
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == (idx+1));
    }

    for (int idx = sizeof(int_nodes)/sizeof(*int_nodes)-1; idx >= 0; idx--)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx+1);
        list_pop_back(&list);
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx);
    }



    /* push back / pop front */

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx);
        list_push_back(&list,&int_nodes[idx]);
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == (idx+1));
    }

    for (int idx = sizeof(int_nodes)/sizeof(*int_nodes)-1; idx >= 0; idx--)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx+1);
        list_pop_front(&list);
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx);
    }



    /* push front / pop front */

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx);
        list_push_front(&list,&int_nodes[idx]);
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == (idx+1));
    }

    for (int idx = sizeof(int_nodes)/sizeof(*int_nodes)-1; idx >= 0; idx--)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx+1);
        list_pop_front(&list);
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx);
    }



    /* push back / pop back */

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx);
        list_push_back(&list,&int_nodes[idx]);
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == (idx+1));
    }

    for (int idx = sizeof(int_nodes)/sizeof(*int_nodes)-1; idx >= 0; idx--)
    {
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx+1);
        list_pop_back(&list);
        UNITTEST_ASSERT("Expected another list size", list_size(&list) == idx);
    }

}

UNITTEST_TESTCASE(begin_front_end_back)
{
    list_t list = {0};

    /* nodes pushed front */

    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_front(&list,&int_nodes[idx]);
    }


    UNITTEST_ASSERT("Expected another node at begin of list", list_begin(&list) == ((list_node_t*)&int_nodes[2]));
    UNITTEST_ASSERT("Expected another node at front of list", list_front(&list) == ((list_node_t*)&int_nodes[2]));
    UNITTEST_ASSERT("Begin of list has to be front of list", list_front(&list) == list_begin(&list));
    UNITTEST_ASSERT("End of list has to be list node itself", list_end(&list) == (&list));
    UNITTEST_ASSERT("Expected another node at back of list", list_back(&list) == ((list_node_t*)&int_nodes[0]));


    /* nodes pushed back */

    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_back(&list,&int_nodes[idx]);
    }

    UNITTEST_ASSERT("Expected another node on begin of list", list_begin(&list) == ((list_node_t*)&int_nodes[0]));
    UNITTEST_ASSERT("Expected another node on front of list", list_front(&list) == ((list_node_t*)&int_nodes[0]));
    UNITTEST_ASSERT("Begin of list has to be front of list", list_front(&list) == list_begin(&list));
    UNITTEST_ASSERT("End of list has to be list node itself", list_end(&list) == (&list));
    UNITTEST_ASSERT("Expected another node at back of list", list_back(&list) == ((list_node_t*)&int_nodes[2]));


    /* Empty list */

    list_init(&list);
    UNITTEST_ASSERT("Expected another node on begin of list", list_begin(&list) == &list);
    UNITTEST_ASSERT("Expected another node on front of list", list_front(&list) == &list);
    UNITTEST_ASSERT("Begin of list has to be front of list", list_front(&list) == &list);
    UNITTEST_ASSERT("End of list has to be list node itself", list_end(&list) == (&list));
    UNITTEST_ASSERT("Expected another node at back of list", list_back(&list) == &list);

    /* Single node */

    list_init(&list);
    list_push_front(&list,&int_nodes[1]);
    UNITTEST_ASSERT("Expected another node on begin of list", list_begin(&list) == ((list_node_t*)&int_nodes[1]));
    UNITTEST_ASSERT("Expected another node on front of list", list_front(&list) == ((list_node_t*)&int_nodes[1]));
    UNITTEST_ASSERT("Begin of list has to be front of list", list_front(&list) == list_begin(&list));
    UNITTEST_ASSERT("End of list has to be list node itself", list_end(&list) == (&list));
    UNITTEST_ASSERT("Expected another node at back of list", list_back(&list) == ((list_node_t*)&int_nodes[1]));
}


UNITTEST_TESTCASE(empty)
{
    list_t list = {0};
    list_init(&list);

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_front(&list,&int_nodes[idx]);
        UNITTEST_ASSERT("List must not be empty", !list_empty(&list));
        UNITTEST_ASSERT("List must contain nodes", list_size(&list) > 0);
    }

    UNITTEST_ASSERT("List must not be empty", !list_empty(&list));
    UNITTEST_ASSERT("List must contain nodes", list_size(&list) > 0);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("List must not be empty", !list_empty(&list));
        UNITTEST_ASSERT("List must contain nodes", list_size(&list) > 0);
        list_pop_front(&list);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);
}

UNITTEST_TESTCASE(find)
{
    list_t list = {0};
    list_init(&list);

    UNITTEST_ASSERT("Node 0 must not be in list", !list_find(&list,&int_nodes[0]));
    UNITTEST_ASSERT("Node 1 must not be in list", !list_find(&list,&int_nodes[1]));
    UNITTEST_ASSERT("Node 2 must not be in list", !list_find(&list,&int_nodes[2]));

    list_push_front(&list,&int_nodes[0]);

    UNITTEST_ASSERT("Node 0 must be in list", list_find(&list,&int_nodes[0]));
    UNITTEST_ASSERT("Node 1 must not be in list", !list_find(&list,&int_nodes[1]));
    UNITTEST_ASSERT("Node 2 must not be in list", !list_find(&list,&int_nodes[2]));

    list_push_back(&list,&int_nodes[1]);

    UNITTEST_ASSERT("Node 0 must be in list", list_find(&list,&int_nodes[0]));
    UNITTEST_ASSERT("Node 1 must be in list", list_find(&list,&int_nodes[1]));
    UNITTEST_ASSERT("Node 2 must not be in list", !list_find(&list,&int_nodes[2]));

    list_push_front(&list,&int_nodes[2]);

    UNITTEST_ASSERT("Node 0 must be in list", list_find(&list,&int_nodes[0]));
    UNITTEST_ASSERT("Node 1 must be in list", list_find(&list,&int_nodes[1]));
    UNITTEST_ASSERT("Node 2 must be in list", list_find(&list,&int_nodes[2]));

    list_erase(&list,&int_nodes[1]);

    UNITTEST_ASSERT("Node 0 must be in list", list_find(&list,&int_nodes[0]));
    UNITTEST_ASSERT("Node 1 must not be in list", !list_find(&list,&int_nodes[1]));
    UNITTEST_ASSERT("Node 2 must be in list", list_find(&list,&int_nodes[2]));

    list_pop_front(&list);

    UNITTEST_ASSERT("Node 0 must be in list", list_find(&list,&int_nodes[0]));
    UNITTEST_ASSERT("Node 1 must not be in list", !list_find(&list,&int_nodes[1]));
    UNITTEST_ASSERT("Node 2 must not be in list", !list_find(&list,&int_nodes[2]));

    list_pop_back(&list);

    UNITTEST_ASSERT("Node 0 must not be in list", !list_find(&list,&int_nodes[0]));
    UNITTEST_ASSERT("Node 1 must not be in list", !list_find(&list,&int_nodes[1]));
    UNITTEST_ASSERT("Node 2 must not be in list", !list_find(&list,&int_nodes[2]));

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);
}


UNITTEST_TESTCASE(push_front_pop_back)
{
    list_t list = {0};
    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_front(&list,&int_nodes[idx]);
    }

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another node", list_back(&list) == (list_node_t*)&int_nodes[idx]);
        list_pop_back(&list);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);

}

UNITTEST_TESTCASE(push_back_pop_front)
{
    list_t list = {0};
    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_back(&list,&int_nodes[idx]);
    }

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another node", list_front(&list) == (list_node_t*)&int_nodes[idx]);
        list_pop_front(&list);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);
}

UNITTEST_TESTCASE(push_back_pop_back)
{
    list_t list = {0};
    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_back(&list,&int_nodes[idx]);
    }

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another node", list_back(&list) == (list_node_t*)&int_nodes[sizeof(int_nodes)/sizeof(*int_nodes)-idx-1]);
        list_pop_back(&list);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);
}

UNITTEST_TESTCASE(push_front_pop_front)
{
    list_t list = {0};
    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_front(&list,&int_nodes[idx]);
    }

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another node", list_front(&list) == (list_node_t*)&int_nodes[sizeof(int_nodes)/sizeof(*int_nodes)-idx-1]);
        list_pop_front(&list);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);
}


UNITTEST_TESTCASE(insert_after)
{
    list_t list = {0};
    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_insert_after(&list,&list,&int_nodes[idx]); // same as push front
    }

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another node", list_back(&list) == (list_node_t*)&int_nodes[idx]);
        list_pop_back(&list);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);
}

UNITTEST_TESTCASE(insert_before)
{
    list_t list = {0};
    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_insert_before(&list,&list,&int_nodes[idx]); // same as push front
    }

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        UNITTEST_ASSERT("Expected another node", list_front(&list) == (list_node_t*)&int_nodes[idx]);
        list_pop_front(&list);
    }

    UNITTEST_ASSERT("List must be empty", list_empty(&list));
    UNITTEST_ASSERT("List must contain no nodes", list_size(&list) == 0);
}

UNITTEST_TESTCASE(next_prev)
{
    list_t list = {0};
    list_init(&list);

    for (int idx = 0; idx < sizeof(int_nodes)/sizeof(*int_nodes); idx++)
    {
        list_push_front(&list,&int_nodes[idx]);
    }

    UNITTEST_ASSERT("Expected another node", list_next(&list,&list) == (list_node_t*)&int_nodes[2]);
    UNITTEST_ASSERT("Expected another node", list_next(&list,list_next(&list,&list)) == (list_node_t*)&int_nodes[1]);
    UNITTEST_ASSERT("Expected another node", list_next(&list,list_next(&list,list_next(&list,&list))) == (list_node_t*)&int_nodes[0]);
    UNITTEST_ASSERT("Expected another node", list_next(&list,list_next(&list,list_next(&list,list_next(&list,&list)))) == &list);

    UNITTEST_ASSERT("Expected another node", list_prev(&list,&list) == (list_node_t*)&int_nodes[0]);
    UNITTEST_ASSERT("Expected another node", list_prev(&list,list_prev(&list,&list)) == (list_node_t*)&int_nodes[1]);
    UNITTEST_ASSERT("Expected another node", list_prev(&list,list_prev(&list,list_prev(&list,&list))) == (list_node_t*)&int_nodes[2]);
    UNITTEST_ASSERT("Expected another node", list_prev(&list,list_prev(&list,list_prev(&list,list_prev(&list,&list)))) == &list);


    UNITTEST_ASSERT("Expected another node", list_prev(&list,(list_node_t*)&int_nodes[1]) == (list_node_t*)&int_nodes[2]);
    UNITTEST_ASSERT("Expected another node", list_next(&list,(list_node_t*)&int_nodes[1]) == (list_node_t*)&int_nodes[0]);
    UNITTEST_ASSERT("Expected another node", list_next(&list,list_prev(&list,(list_node_t*)&int_nodes[1])) == (list_node_t*)&int_nodes[1]);
    UNITTEST_ASSERT("Expected another node", list_prev(&list,list_next(&list,(list_node_t*)&int_nodes[1])) == (list_node_t*)&int_nodes[1]);

}


#define UNITTEST_TESTSUITE_EXP(x) \
    UNITTEST_TESTSUITE(x)



UNITTEST_TESTSUITE_EXP(unittest_list_type)
{
    UNITTEST_TESTSUITE_BEGIN();

    UNITTEST_EXEC_TESTCASE(init);
    UNITTEST_EXEC_TESTCASE(push_front);
    UNITTEST_EXEC_TESTCASE(push_back);
    UNITTEST_EXEC_TESTCASE(clear);
    UNITTEST_EXEC_TESTCASE(size);
    UNITTEST_EXEC_TESTCASE(begin_front_end_back);
    UNITTEST_EXEC_TESTCASE(empty);
    UNITTEST_EXEC_TESTCASE(find);
    UNITTEST_EXEC_TESTCASE(push_front_pop_back);
    UNITTEST_EXEC_TESTCASE(push_back_pop_front);
    UNITTEST_EXEC_TESTCASE(push_front_pop_front);
    UNITTEST_EXEC_TESTCASE(push_back_pop_back);
    UNITTEST_EXEC_TESTCASE(insert_after);
    UNITTEST_EXEC_TESTCASE(insert_before);
    UNITTEST_EXEC_TESTCASE(next_prev);

    UNITTEST_TESTSUITE_END();
}
