#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

#define NAME_LENGTH 50

struct birthday_list 
{
    char name[NAME_LENGTH];
    int day;
    int month;
    int year;
    struct list_head link_prev_next;
};

struct list_head *all_birthdays;


void printk_birthdays(struct list_head * list_all)
{
  struct list_head *pos;
  struct birthday_list *tmp;

  printk(KERN_INFO "Prikaz rodjendana pomocu list_for_each()\n");
  list_for_each(pos, list_all)
  {
    tmp= list_entry(pos, struct birthday_list, link_prev_next);
    printk( KERN_INFO "%s %d.%d.%d\n", 
              tmp->name, tmp->day, tmp->month, tmp->year);
  }
  printk(KERN_INFO "\n");
}

void recycle_birthdays(struct list_head * list_all)
{
  struct list_head *pos, *q;
  struct birthday_list *tmp;

  printk(KERN_INFO 
           "Uklanjanje rodjendana pomocu list_for_each_safe()\n");
  list_for_each_safe(pos, q, list_all)
  {
    tmp= list_entry(pos, struct birthday_list, link_prev_next);
    printk(KERN_INFO "Uklanjanje: %s %d.%d.%d\n", 
           tmp->name, tmp->day, tmp->month, tmp->year);	 
    list_del(pos);
    kfree(tmp);
  }
}

/* This function is called when the module is loaded. */
int birthdays_init(void)
{
  struct birthday_list *person;
  
  printk(KERN_INFO "rodjendani: Ucitan je modul\n");

  printk(KERN_INFO "rodjendani: Kreirannje podataka\n");

  INIT_LIST_HEAD( all_birthdays );

  person = (struct birthday_list *) 
             kmalloc(sizeof(*person), GFP_KERNEL);
  strcpy( person->name, "Jovan" );
  person->day = 1;
  person->month= 8;
  person->year = 1929;
  list_add(&(person->link_prev_next), all_birthdays);

  person = (struct birthday_list *) 
              kmalloc(sizeof(*person), GFP_KERNEL);
  strcpy( person->name, "Mileva" );
  person->day = 4;
  person->month= 9;
  person->year = 1936;
  list_add(&(person->link_prev_next), all_birthdays);

  person = (struct birthday_list *) 
              kmalloc(sizeof(*person), GFP_KERNEL);
  strcpy( person->name, "Nebojsa" );
  person->day = 10;
  person->month= 8;
  person->year = 1969;
  list_add(&(person->link_prev_next), all_birthdays);

  person = (struct birthday_list *) 
              kmalloc(sizeof(*person), GFP_KERNEL);
  strcpy( person->name, "Slobodan" );
  person->day = 27;
  person->month= 2;
  person->year = 1971;
  list_add(&(person->link_prev_next), all_birthdays);

  person = (struct birthday_list *) 
              kmalloc(sizeof(*person), GFP_KERNEL);
  strcpy( person->name, "Sanja" );
  person->day = 10;
  person->month= 4;
  person->year = 1972;
  list_add(&(person->link_prev_next), all_birthdays);

  person = (struct birthday_list *) 
              kmalloc(sizeof(*person), GFP_KERNEL);
  strcpy( person->name, "Sofija" );
  person->day = 18;
  person->month= 12;
  person->year = 2003;
  list_add(&(person->link_prev_next), all_birthdays);

  printk(KERN_INFO "rodjendani: Prikaz kreiranih podataka\n");
  //printk_birthdays( all_birthdays );
  return 0;
}

/* This function is called when the module is removed. */
void birthdays_exit(void)
{
  printk(KERN_INFO "rodjendani: Uklanjanje kreiranih podataka\n");
  //recycle_birthdays( all_birthdays );
  printk(KERN_INFO "rodjendani: Uklonjen je modul\n");
}

/* Macros for registering module entry and exit points. */
module_init(birthdays_init);
module_exit(birthdays_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Rodjendani2 - Dvostuko povezana lista");
MODULE_AUTHOR("Ja");

