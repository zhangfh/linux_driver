#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */

#include <linux/init.h> /* Needed for the macros */

#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/stat.h>

/*
int init_module(void)
{
	printk(KERN_INFO "Hello world 1.\n");
	// A non 0 return means init_module failed; module can't be loaded.
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world 1.\n");
}
*/
/*
static int __init hello_2_init(void)
{
	printk(KERN_INFO "Hello, world 2\n");
	return 0;
}
static void __exit hello_2_exit(void)
{
	printk(KERN_INFO "Goodbye, world 2\n");
}

module_init(hello_2_init);
module_exit(hello_2_exit);
*/
/*
static int hello3_data __initdata = 3;
static int __init hello_3_init(void)
{
	printk(KERN_INFO "Hello, world %d\n", hello3_data);
	return 0;
}
static void __exit hello_3_exit(void)
{
	printk(KERN_INFO "Goodbye, world 3\n");
}

module_init(hello_3_init);
module_exit(hello_3_exit)
*/

#define DRIVER_AUTHOR "Peter Jay Salzman <p@dirac.org>"
#define DRIVER_DESC "A sample driver"
/*
static int __init init_hello_4(void)
{
	printk(KERN_INFO "Hello, world 4\n");
	return 0;
}
static void __exit cleanup_hello_4(void)
{
	printk(KERN_INFO "Goodbye, world 4\n");
}
module_init(init_hello_4);
module_exit(cleanup_hello_4);

//Get rid of taint message by declaring code as GPL.
//MODULE_LICENSE("GPL");
//Or with defines, like this:
MODULE_AUTHOR(DRIVER_AUTHOR); //Who wrote this module? 
MODULE_DESCRIPTION(DRIVER_DESC); // What does this module do 

// This module uses /dev/testdevice. The MODULE_SUPPORTED_DEVICE macro might
//be used in the future to help automatic configuration of modules, but is
//currently unused other than for documentation purposes.

MODULE_SUPPORTED_DEVICE("testdevice");
*/

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "blah";
static int myintArray[2] = {-1,-1};
static int arr_argc = 0;

module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short integer");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An integer");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long integer");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");

module_param_array(myintArray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintArray, "An array of integers");

static int __init hello_5_init(void)
{
	int i;
	printk(KERN_INFO "Hello, world 5\n=============\n");
	printk(KERN_INFO "myshort is a short integer: %hd\n", myshort);
	printk(KERN_INFO "myint is an integer: %d\n", myint);
	printk(KERN_INFO "mylong is a long integer: %ld\n", mylong);
	printk(KERN_INFO "mystring is a string: %s\n", mystring);
	for (i = 0; i < (sizeof myintArray / sizeof (int)); i++)
	{
		printk(KERN_INFO "myintArray[%d] = %d\n", i, myintArray[i]);
	}
	printk(KERN_INFO "got %d arguments for myintArray.\n", arr_argc);
	return 0;
}
static void __exit hello_5_exit(void)
{
	printk(KERN_INFO "Goodbye, world 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);

