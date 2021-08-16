#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>

struct message{
  unsigned char* _msg;
  long _len;
  struct list_head msg_linker;
};

struct mystruct{
  struct list_head mylist;
  unsigned long id;
  int num_msg;
  struct list_head messages;
};

struct list_head mylinkedlist;
LIST_HEAD(mylinkedlist);
long COUNT = 0;


SYSCALL_DEFINE1(create_mbox_421, unsigned long, id){
  struct mystruct* first = kmalloc(sizeof(struct mystruct), GFP_KERNEL);
  struct mystruct* dataptr = NULL;

  if(COUNT > 0)
    {
      list_for_each_entry(dataptr, &mylinkedlist, mylist)
	{
	  if(dataptr->id == id)
	    {
	      return -EEXIST;
	    }
	}
    }
  first->id = id;
  first->num_msg = 0;
  list_add_tail(&first->mylist, &mylinkedlist);
  COUNT++;

  return 0;
}

SYSCALL_DEFINE1(remove_mbox_421, unsigned long, id){
  struct list_head* position = NULL;
  struct list_head* temp;
  struct mystruct* p;
  
  list_for_each_safe(position, temp, &mylinkedlist)
    {
      p = list_entry(position, struct mystruct, mylist);
      if(p->id == id && p->num_msg == 0)
	{
	  list_del(position);
	  kfree(p);
	  COUNT--;
	  return 0;
	}
    }
   return -ENOENT;
}

SYSCALL_DEFINE0(reset_mbox_421){

  struct list_head* position = NULL;
  struct list_head* temp;
  struct list_head* msg_pos = NULL;
  struct list_head* temp2;
  struct mystruct* p;
  struct message* x;

  if(COUNT > 0){
    list_for_each_safe(position, temp, &mylinkedlist){
      p = list_entry(position, struct mystruct, mylist);
      if(p->num_msg > 0)
	{
	  list_for_each_safe(msg_pos, temp2, &p->messages){
	    x = list_entry(msg_pos, struct message, msg_linker);
	    list_del(&x->msg_linker);
	    kfree(x);
	}
	}
      
      list_del(&p->mylist);
      kfree(p);
      COUNT--;
    }
  }
  return 0;
}
SYSCALL_DEFINE0(count_mbox_421){ return COUNT; }

SYSCALL_DEFINE2(list_mbox_421, unsigned long __user*, mbxes, long, k){
  long index = 0;
  struct list_head* position = NULL;
  struct mystruct* p;
 
  if(COUNT > 0){
    list_for_each(position, &mylinkedlist){
      if(index < COUNT && index < k){
	p = list_entry(position, struct mystruct, mylist);
	*(mbxes + index) = p->id;
      }
      index++;
    }
    return 0;
  }
  return -EACCES;
}

SYSCALL_DEFINE3(send_msg_421, unsigned long, id, const unsigned char __user*, msg, long, n){
  
  struct mystruct *dataptr = NULL;
  struct message* new_msg;
  size_t size_n = n;
  long i;  

  if(n < 0)
    return -EFAULT; 
  
  list_for_each_entry(dataptr, &mylinkedlist, mylist)
    {
      if(dataptr->id == id){
	dataptr->num_msg = dataptr->num_msg + 1;
	INIT_LIST_HEAD(&dataptr->messages);

	new_msg = (struct message*)kmalloc(sizeof(struct message), GFP_KERNEL);
	new_msg->_msg = (unsigned char*)kmalloc(size_n, GFP_KERNEL);

	for(i=0; i<n; i++){
	  new_msg->_msg[i] = msg[i]; }
	new_msg->_len = n;
	list_add_tail(&new_msg->msg_linker, &dataptr->messages);
	return 0;
      }
    }
  return -ENOENT;
}

SYSCALL_DEFINE3(recv_msg_421, unsigned long, id, unsigned char __user*, msg, long, n){

  struct list_head* position = NULL;
  struct list_head* temp;
  struct list_head* msg_pos = NULL;
  struct list_head* temp2;
  struct mystruct* p;
  struct message* x;
  long i; 

  list_for_each_safe(position, temp, &mylinkedlist){
    p = list_entry(position, struct mystruct, mylist);
    if(p->id == id && p->num_msg > 0)
      {
	list_for_each_safe(msg_pos, temp2, &p->messages){
	  x = list_entry(msg_pos, struct message, msg_linker);
	  
	  for(i=0; i<n; i++){
	    msg[i] = x->_msg[i]; }
	  
	  list_del(&x->msg_linker);
	  kfree(x);
	  p->num_msg = p->num_msg - 1;
	  return 0;
	}
      }
  }
  return -ENOENT;
}

SYSCALL_DEFINE3(peek_msg_421, unsigned long, id, unsigned char __user*, msg, long, n){

  struct list_head* position = NULL;
  struct list_head* temp;
  struct list_head* msg_pos = NULL;
  struct list_head* temp2;
  struct mystruct* p;
  struct message* x;
  long i;
  
  list_for_each_safe(position, temp, &mylinkedlist){
    p = list_entry(position, struct mystruct, mylist);
    if(p->id == id)
      {
	list_for_each_safe(msg_pos, temp2, &p->messages){
	  x = list_entry(msg_pos, struct message, msg_linker);
	  
	  for(i=0; i<n; i++){
	    msg[i] = x->_msg[i]; }

	  return 0;
	}
      }
  }
  return -ENOENT;
}

SYSCALL_DEFINE1(count_msg_421, unsigned long, id){

  struct mystruct *dataptr = NULL;
  
  list_for_each_entry(dataptr, &mylinkedlist, mylist)
    {
      if(dataptr->id == id)
	return dataptr->num_msg;
    }
  return -ENOENT;
}

SYSCALL_DEFINE1(len_msg_421, unsigned long, id){

  struct mystruct *dataptr = NULL;
  struct message* msgptr = NULL;
  size_t size;
  long l_size;
  list_for_each_entry(dataptr, &mylinkedlist, mylist)
    {
      if(dataptr->id == id && dataptr->num_msg > 0 )
	{
	  list_for_each_entry(msgptr, &dataptr->messages, msg_linker)
	    {
	      size = sizeof(msgptr->_msg);
	      l_size = (unsigned long)(size);
	      return l_size;
	    }
	}
    }
  return -EPERM;
}

SYSCALL_DEFINE1(print_mbox_421, unsigned long, id){
  
  struct mystruct *dataptr = NULL;
  struct message* msgptr = NULL;
  long i;
 
  list_for_each_entry(dataptr, &mylinkedlist, mylist)
    {
      if(dataptr->id == id)
	{
	  list_for_each_entry(msgptr, &dataptr->messages, msg_linker)
	    {  
	      for(i=0; i < msgptr->_len; i++){
		printk(KERN_CONT "%02x ", msgptr->_msg[i]);}
	      printk("\n---\n");
	    }
	  return 0;
	}
    }
  return -ENOENT;
}
