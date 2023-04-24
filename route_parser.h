/** @file route_parser.h */
#ifndef ROUTE_PARSER_ROUTE_PARSER_H
#define ROUTE_PARSER_ROUTE_PARSER_H


#include <stdint.h>
#include <stdbool.h>


/********************************************//**
 * @brief the max size of the path string
 ***********************************************/
#define RP_PATH_LIMIT 2048

#define RP_DEBUG true
#define RP_ALLOC_ERROR 1
#define RP_NO_ERROR 0

enum RP_Errors {
    RouteAssignError = 0
};


typedef struct RP_Route
{
    char *path;
} RP_Route;

typedef struct _RP_Node
{
    RP_Route *route;
    struct _RP_Node *next;
} _RP_Node;

/********************************************//**
 * @brief
 ***********************************************/
typedef struct RP_Path
{
    char *path;
    struct
    {
        char *name;
        char *value;
    } *query;
    char *fragment;
    int length;
    int max_routes;
    char *result;
    bool matched;
    RP_Route *route;
    _RP_Node *_nodes;
} RP_Path;

RP_Path *RP_Path_new(const char *path_str, int max_routes, int len, char routes[len][256]);

void RP_Path_compare(RP_Path *p, int len, char routes[len][256]);

void *RP_Path_clean(RP_Path *p);

void RP_PrintError(enum RP_Errors err);

// static
static _RP_Node *_RP_Node_new(RP_Route *route);
static bool _RP_Node_insert(_RP_Node *const node, RP_Route *route);

#endif //ROUTE_PARSER_ROUTE_PARSER_H
