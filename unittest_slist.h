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
    \file   unittest_slist.h

    \brief

    \details
*/

#ifndef UNITTEST_SLIST_H_
#define UNITTEST_SLIST_H_

#include "slist.h"

#define unittest_list_type slist

typedef slist_t list_t;

#define list_node_t             slist_node_t
#define list_t                  slist_t
#define list_t                  slist_t
#define LIST_NODE_TYPE          SLIST_NODE_TYPE

#define list_next               slist_next
#define list_prev               slist_prev
#define list_init               slist_init
#define list_begin              slist_begin
#define list_front              slist_front
#define list_end                slist_end
#define list_back               slist_back
#define list_foreach            slist_foreach
#define list_empty              slist_empty
#define list_push_front         slist_push_front
#define list_pop_front          slist_pop_front
#define list_push_back          slist_push_back
#define list_pop_back           slist_pop_back
#define list_insert_after       slist_insert_after
#define list_insert_before      slist_insert_before
#define list_clear              slist_clear
#define list_erase              slist_erase
#define list_size               slist_size
#define list_find               slist_find




#endif /* UNITTEST_SLIST_H_ */
