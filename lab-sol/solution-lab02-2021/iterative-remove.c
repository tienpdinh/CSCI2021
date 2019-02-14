  

// Add the given data in sorted order to the list
int list_add(list_t *list, char *new_data){
  if(list->size == 0){

  }
  if(head){

  }
  // locate the correct insertion point forthe

  node_t *prev = list->head;
  while(prev->next != NULL){
    int diff = strcmp(new_data, prev->next->data); // compare new_data to next node
    if(diff == 0){                                 // no differences between old/new data
      return 0;                                    // duplicate, don't add
    }
    if(diff < 0){                                  // found insertion point
      break;                                       // break out of loop
    }                                              // 
    prev = prev->next;                             // insertion point not found yet, advance

  }
  // prev no positioned at node prior correct position for new node
  node_t *new_node = malloc(sizeof(node_t));   // allocate
  strcpy(new_node->data, new_data);            // copy data
  new_node->next = prev->next;                 // link to next
  prev->next = new_node;                       // link prev to new
  return 1;                                    // successful insert
    }
}
