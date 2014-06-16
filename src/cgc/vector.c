/**
 * \file vector.c
 * \author RAZANAJATO RANAIVOARIVONY Harenome
 * \date 2014
 * \copyright LGPLv3
 */
/* Copyright © 2014 RAZANAJATO RANAIVOARIVONY Harenome.
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * and the GNU General Public License along with this program.
 * If not, see http://www.gnu.org/licenses/.
 */
#include "cgc/vector.h"

static const size_t _DEFAULT_SIZE_STEP = 128;

cgc_vector * cgc_vector_new (size_t element_size, size_t size)
{
    size_t size_step = size != 0 ? size : _DEFAULT_SIZE_STEP;

    cgc_vector * vector = malloc (sizeof * vector);
    if (vector != NULL)
    {
        vector->_content = malloc (size_step * element_size);
        if (vector->_content != NULL)
        {
            vector->_size = 0;
            vector->_max_size = size_step;
            vector->_size_step = size_step;
            vector->_element_size = element_size;
        }
        else
        {
            free (vector);
            vector = NULL;
        }
    }

    return vector;
}

void cgc_vector_free (cgc_vector * vector)
{
    if (vector != NULL)
        free (vector->_content);
    free (vector);
}

bool cgc_vector_is_empty (const cgc_vector * vector)
{
    return vector->_size == 0;
}

size_t cgc_vector_size (const cgc_vector * vector)
{
    return vector->_size;
}

size_t cgc_vector_max_size (const cgc_vector * vector)
{
    return vector->_max_size;
}

static inline void * _cgc_vector_address (cgc_vector * vector, size_t i)
{
    char * v = vector->_content;
    return v + i * vector->_element_size;
}

static inline int _cgc_vector_grow (cgc_vector * vector, size_t new_size)
{
    void * new_content = realloc (vector->_content, new_size * vector->_element_size);
    if (new_content != NULL)
    {
        vector->_content = new_content;
        vector->_max_size = new_size;
    }
    return 0;
}

int cgc_vector_push_back (cgc_vector * vector, void * element)
{
    if (vector != NULL)
    {
        if (vector->_size >= vector->_max_size)
            _cgc_vector_grow (vector, vector->_max_size + vector->_size_step);

        void * v = _cgc_vector_address (vector, vector->_size);
        memcpy (v, element, vector->_element_size);
        vector->_size++;
    }
    return 0;
}

void * cgc_vector_pop_back (cgc_vector * vector)
{
    void * element = NULL;
    if (vector != NULL)
    {
        void * back = cgc_vector_back (vector);
        element = malloc (vector->_element_size);
        memcpy (element, back, vector->_element_size);
        vector->_size--;
    }
    return element;
}

void * cgc_vector_at (cgc_vector * vector, size_t i)
{
    return _cgc_vector_address (vector, i);
}

void * cgc_vector_front (cgc_vector * vector)
{
    return _cgc_vector_address (vector, 0);
}

void * cgc_vector_back (cgc_vector * vector)
{
    int back = vector->_size > 0 ? vector->_size - 1 : 0;
    return _cgc_vector_address (vector, back);
}

void cgc_vector_clear (cgc_vector * vector)
{
    vector->_size = 0;
}
