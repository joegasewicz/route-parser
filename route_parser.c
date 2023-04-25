/** @file route_parser.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./route_parser.h"

#define RP_NO_MATCH NULL
#define RP_ARR_STR_SIZE(r) sizeof(r)/sizeof(r[0])
#define RP_MAX_ROUTES 256


/********************************************//**
 * @brief Creates a new RP_Path object that contains
 * all the meta level path segment details.
 *
 * @param path_str const char*
 * @return RP_PATH*
 *
 ***********************************************/
RP_Path *RP_Path_new(const char *path_str, int max_routes, int len, char routes[len][256])
{
    int count = len;
    RP_Path *p = malloc(sizeof(RP_Path));
    int length = strlen(path_str) + 1;
    p->path = malloc(length);
    strcpy(p->path, path_str);
    p->length = length;
    if (!max_routes)
        p->max_routes = RP_MAX_ROUTES;
    p->matched = false;
    // _nodes
    RP_Route *first_r = malloc(sizeof(RP_Route));
    _RP_Node *route_n = _RP_Node_new(first_r);
    bool ins = _RP_Node_insert(route_n, first_r);
    while (count > 0)
    {
        RP_Route *r = malloc(sizeof(RP_Route));
        r->path = malloc(sizeof(routes[count])); // TODO free
        strcpy(r->path, routes[count]);
        if (count == len)
        {
            ins = _RP_Node_insert(route_n, r);
        }
        else
        {
            _RP_Node *n = _RP_Node_new(r);
            ins = _RP_Node_insert(n, r);
        }
        if (!ins) break;
        count--;
    }
    p->_nodes = route_n;
    if (RP_DEBUG)
    {
        printf("Creating PR_Path with the following settings:\n"
               "\t- max_routes: %d\n"
               "\t- matched: %d\n",
               p->max_routes, p->matched);
    }
    return p;
}


/********************************************//**
 * @brief Compares the current path to an array of
 * routes represented as strings. If a route matches
 * the current path then that route is set on
 * `RP_Path.result`. If there is no match then
 * `RP_Path.matched` is set to false, true if a
 *  route is successfully matched.
 *
 * @param route const char*s
 * @return
 *
 *******************************************s****/
void RP_Path_compare(RP_Path *p, int len, char routes[len][256])
{
    for (int i = 0; i < len; i++)
    {
        if (strcmp(routes[i], p->path) == 0)
        {
            p->matched = true;
            p->result = malloc(sizeof(char) * 256);
            strcpy(p->result, routes[i]);
        }
    }
}

/********************************************//**
 * @brief
 *
 * @param p RP_PATH*
 * @return void*
 *
 ***********************************************/
void *RP_Path_clean(RP_Path *p)
{
    _RP_Node * tmpPtr;
    free(p->result);
    while(p->_nodes->next != NULL)
    {
        if (p->_nodes->next == NULL)
        {
            free(p->_nodes);
        }
        tmpPtr = p->_nodes;
        p->_nodes = p->_nodes->next;
        if (tmpPtr)
            free(tmpPtr);
    }
    free(p->_nodes);
    free(p);
}

/** @brief
 *
 * @param err enum RP_Errors
 * @return void
 *
 */
void RP_PrintError(enum RP_Errors err)
{
    switch (err)
    {
        case RouteAssignError:
            printf("Error assigning route\n");
    }
}

/***************************************************/
/***************************************************
* Core
****************************************************/
/***************************************************/
static _RP_Node *RP_Node_new(RP_Route *route)
{
    _RP_Node *n = malloc(sizeof(_RP_Node));
    n->route = route;
    n->next = NULL;
    return n;
}

static bool _RP_Node_insert(_RP_Node *const node, RP_Route *route)
{
    _RP_Node *temp_node = node;
    while(temp_node->next != NULL)
    {
        temp_node = temp_node->next;
    }
    temp_node->next = malloc(sizeof(_RP_Node));
    if (temp_node->next == NULL)
    {
        printf("Error: unable to allocate memory");
        return false;
    }
    temp_node->next->route = route;
    temp_node->next->next = NULL;
    return true;
}