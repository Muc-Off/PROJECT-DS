#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data_structure.h"

struct stall *create_stall(int stall_id, char *stall_name, char *contact_number)
{
    struct stall *v = (struct stall *)malloc(sizeof(struct stall));
    if (v == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    v->stall_id = stall_id;

    if (stall_name != NULL)
    {
        strcpy(v->stall_name, stall_name);
    }

    if (contact_number != NULL)
    {
        strcpy(v->contact_number, contact_number);
    }

    v->next = NULL;
    v->prev = NULL;
    return v;
}

void add_stall(struct stall **head, int stall_id, char *stall_name, char *contact_number)
{
    struct stall *v = create_stall(stall_id, stall_name, contact_number);
    if (v == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = v;
        return;
    }

    struct stall *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = v;
    v->prev = current;
}

void delete_stall(struct stall **head, int stall_id)
{
    struct stall *current = *head;
    while (current != NULL && current->stall_id != stall_id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found.\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }

    free(current);
}

struct stall *search_stall_by_name(struct stall *head, char *stall_name)
{
    if (stall_name == NULL)
    {
        return NULL;
    }

    struct stall *current = head;
    while (current != NULL)
    {
        if (strcmp(current->stall_name, stall_name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void display_all_stalls(struct stall *head)
{
    if (head == NULL)
    {
        printf("No stall records found\n");
        return;
    }

    printf("\n");
    printf(" STALL DATABASE \n");
    int count = 0;
    struct stall *v = head;
    while (v != NULL)
    {
        count++;
        printf("Entry #%d\n", count);
        printf("  ID: %d\n", v->stall_id);
        printf("  Name: %s\n", v->stall_name);
        printf("  Contact: %s\n", v->contact_number);
        printf("---\n");
        v = v->next;
    }
    printf("Total stalls: %d\n\n\n", count);
}

void free_all_stalls(struct stall *head)
{
    struct stall *current = head;
    while (current != NULL)
    {
        struct stall *temp = current;
        current = current->next;
        free(temp);
    }
}

struct item *create_item(int item_id, char *item_name, float price, int quantity_available, int stall_id)
{
    struct item *item = (struct item *)malloc(sizeof(struct item));
    if (item == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    item->item_id = item_id;
    item->price = (price >= 0) ? price : 0.0;
    item->quantity_available = (quantity_available >= 0) ? quantity_available : 0;
    item->stall_id = stall_id;

    if (item_name != NULL)
    {
        strcpy(item->item_name, item_name);
    }

    item->next = NULL;
    item->prev = NULL;
    return item;
}

void add_item(struct item **head, int item_id, char *item_name, float price, int quantity_available, int stall_id)
{
    struct item *item = create_item(item_id, item_name, price, quantity_available, stall_id);
    if (item == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = item;
        return;
    }

    struct item *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = item;
    item->prev = tail;
}

void delete_item(struct item **head, int item_id)
{
    struct item *current = *head;
    while (current != NULL && current->item_id != item_id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found.\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }
    free(current);
}

struct item *search_item_by_name(struct item *head, char *item_name)
{
    if (item_name == NULL)
    {
        return NULL;
    }

    struct item *it = head;
    while (it != NULL)
    {
        if (strcmp(it->item_name, item_name) == 0)
        {
            return it;
        }
        it = it->next;
    }
    return NULL;
}

struct item *search_item(struct item *head, int item_id)
{
    struct item *it = head;
    while (it != NULL)
    {
        if (it->item_id == item_id)
        {
            return it;
        }
        it = it->next;
    }
    return NULL;
}

void display_items_by_stall(struct item *head, int stall_id)
{
    if (head == NULL)
    {
        printf("No items in inventory\n");
        return;
    }

    printf("\n STALL %d INVENTORY \n", stall_id);
    int count = 0;

    struct item *it = head;
    while (it != NULL)
    {
        if (it->stall_id == stall_id)
        {
            count++;
            printf("Item #%d\n", count);
            printf("  ID: %d\n", it->item_id);
            printf("  Product: %s\n", it->item_name);
            printf("  Price: %.2f BDT.\n", it->price);
            printf("  In Stock: %d units\n\n", it->quantity_available);
        }
        it = it->next;
    }

    if (count == 0)
    {
        printf("No items found for stall %d\n", stall_id);
    }
    else
    {
        printf("Total items: %d\n", count);
    }
    printf("\n\n");
}

char* get_stall_name_by_id(struct stall *head, int stall_id)
{
    struct stall *current = head;
    while (current != NULL)
    {
        if (current->stall_id == stall_id)
        {
            return current->stall_name;
        }
        current = current->next;
    }
    return "Unknown Stall";
}

void display_all_items(struct item *head, struct stall *stall_head)
{
    if (head == NULL)
    {
        printf("Inventory is empty\n");
        return;
    }

    printf("\n COMPLETE INVENTORY \n");
    int count = 0;
    float total_value = 0;

    struct item *it = head;
    while (it != NULL)
    {
        count++;
        printf("Item #%d\n", count);
        printf("  ID: %d | Stall: %s\n", it->item_id, get_stall_name_by_id(stall_head, it->stall_id));
        printf("  Name: %s\n", it->item_name);
        printf("  Unit Price: BDT%.2f\n", it->price);
        printf("  Quantity: %d\n", it->quantity_available);
        total_value += it->price * it->quantity_available;
        printf("\n");
        it = it->next;
    }

    printf("Total items in inventory: %d\n", count);
    printf("Total inventory value: %.2f BDT.\n", total_value);
}

void update_item_quantity(struct item *head, int item_id, int new_quantity)
{
    struct item *it = search_item(head, item_id);
    if (it == NULL)
    {
        printf("not found.\n");
        return;
    }

    int old_qty = it->quantity_available;
    it->quantity_available = (new_quantity >= 0) ? new_quantity : 0;
    printf("Item %d: quantity updated from %d to %d\n", item_id, old_qty, it->quantity_available);
}

void free_all_items(struct item *head)
{
    struct item *current = head;
    while (current != NULL)
    {
        struct item *temp = current;
        current = current->next;
        free(temp);
    }
}

struct customer *create_customer(char *customer_id, char *customer_name, char *contact_number)
{
    struct customer *customer = (struct customer *)malloc(sizeof(struct customer));
    if (customer == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    if (customer_id != NULL)
    {
        strcpy(customer->customer_id, customer_id);
    }

    if (customer_name != NULL)
    {
        strcpy(customer->customer_name, customer_name);
    }

    if (contact_number != NULL)
    {
        strcpy(customer->contact_number, contact_number);
    }

    customer->next = NULL;
    customer->prev = NULL;
    return customer;
}

void add_customer(struct customer **head, char *customer_id, char *customer_name, char *contact_number)
{
    struct customer *customer = create_customer(customer_id, customer_name, contact_number);
    if (customer == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = customer;
        return;
    }

    struct customer *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = customer;
    customer->prev = tail;
}

void delete_customer(struct customer **head, char *customer_id)
{
    if (customer_id == NULL)
    {
        return;
    }

    struct customer *current = *head;
    while (current != NULL && strcmp(current->customer_id, customer_id) != 0)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found.\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }
    free(current);
}

void free_all_customers(struct customer *head)
{
    struct customer *current = head;
    while (current != NULL)
    {
        struct customer *temp = current;
        current = current->next;
        free(temp);
    }
}

struct cart *create_cart(int cart_id, char *customer_id, int item_id, int quantity, float item_price)
{
    struct cart *entry = (struct cart *)malloc(sizeof(struct cart));
    if (entry == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    entry->cart_id = cart_id;
    entry->item_id = item_id;
    entry->quantity = (quantity > 0) ? quantity : 0;
    entry->item_price = (item_price >= 0) ? item_price : 0.0;

    if (customer_id != NULL)
    {
        strcpy(entry->customer_id, customer_id);
    }

    entry->next = NULL;
    entry->prev = NULL;
    return entry;
}

void add_to_cart(struct cart **head, int cart_id, char *customer_id, int item_id, int quantity, float item_price)
{
    struct cart *entry = create_cart(cart_id, customer_id, item_id, quantity, item_price);
    if (entry == NULL)
    {
        return;
    }
    if (*head == NULL)
    {
        *head = entry;
        return;
    }

    struct cart *tail = *head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = entry;
    entry->prev = tail;
}

void remove_from_cart(struct cart **head, int cart_id)
{
    struct cart *current = *head;
    while (current != NULL && current->cart_id != cart_id)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        printf("not found.\n");
        return;
    }

    if (current == *head)
    {
        *head = current->next;
        if (*head != NULL)
        {
            (*head)->prev = NULL;
        }
    }
    else
    {
        if (current->prev != NULL)
        {
            current->prev->next = current->next;
        }
        if (current->next != NULL)
        {
            current->next->prev = current->prev;
        }
    }
    free(current);
}
void display_cart(struct cart *head, char *customer_id)
{
    if (head == NULL)
    {
        printf("No items in carts\n");
        return;
    }

    if (customer_id == NULL)
    {
        printf("ERROR: Customer ID required\n");
        return;
    }

    printf("\n SHOPPING CART: %s \n", customer_id);
    int item_count = 0;
    float total = 0.0;

    struct cart *entry = head;
    while (entry != NULL)
    {
        if (strcmp(entry->customer_id, customer_id) == 0)
        {
            item_count++;
            float subtotal = entry->quantity * entry->item_price;
            printf("Cart Entry #%d\n", entry->cart_id);
            printf(" Item ID: %d\n", entry->item_id);
            printf(" Qty: %d Pcs.\nUnit Price = %.2f BDT.\n Total = %.2f BDT.\n", entry->quantity, entry->item_price, subtotal);
            total += subtotal;
        }
        entry = entry->next;
    }

    if (item_count == 0)
    {
        printf("Cart is empty for customer %s\n", customer_id);
    }
    else
    {
        printf("\nItems in cart: %d\n", item_count);
        printf("Total: %.2f BDT.\n", total);
    }
    printf("\n\n");
}

float calculate_cart_total(struct cart *head, char *customer_id)
{
    if (customer_id == NULL)
        return 0.0;

    float total = 0.0;
    struct cart *entry = head;
    while (entry != NULL)
    {
        if (strcmp(entry->customer_id, customer_id) == 0)
        {
            total += entry->quantity * entry->item_price;
        }
        entry = entry->next;
    }
    return total;
}

void free_all_cart(struct cart *head)
{
    struct cart *current = head;
    while (current != NULL)
    {
        struct cart *temp = current;
        current = current->next;
        free(temp);
    }
}
