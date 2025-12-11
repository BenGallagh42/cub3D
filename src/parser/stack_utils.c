/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkomasat <kkomasat@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 01:06:50 by kkomasat          #+#    #+#             */
/*   Updated: 2025/12/11 01:06:52 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initialize stack with given capacity
t_stack *init_stack(int capacity)
{
    t_stack *stack;

    stack = (t_stack *)malloc(sizeof(t_stack));
    if (!stack)
        return (NULL);
    stack->data = (t_point *)malloc(sizeof(t_point) * capacity);
    if (!stack->data)
    {
        free(stack);
        return (NULL);
    }
    stack->top = -1;
    stack->capacity = capacity;
    return (stack);
}

// Free stack memory
void free_stack(t_stack *stack)
{
    if (stack)
    {
        if (stack->data)
            free(stack->data);
        free(stack);
    }
}

// Push point onto stack (returns 0 on failure, 1 on success)
int stack_push(t_stack *stack, int x, int y)
{
    t_point *new_data;

    if (stack->top >= stack->capacity - 1)
    {
        new_data = (t_point *)malloc(sizeof(t_point) * stack->capacity * 2);
        if (!new_data)
            return (0);
        ft_memcpy(new_data, stack->data, sizeof(t_point) * stack->capacity);
        free(stack->data);
        stack->data = new_data;
        stack->capacity *= 2;
    }
    stack->top++;
    stack->data[stack->top].x = x;
    stack->data[stack->top].y = y;
    return (1);
}

// Pop point from stack (returns 1 if popped, 0 if empty)
int stack_pop(t_stack *stack, int *x, int *y)
{
    if (stack->top < 0)
        return (0);
    *x = stack->data[stack->top].x;
    *y = stack->data[stack->top].y;
    stack->top--;
    return (1);
}

// Check if stack is empty
int stack_is_empty(t_stack *stack)
{
    return (stack->top < 0);
}