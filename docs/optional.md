- uses a boolean flag to mark whether its a null value or not

- regarding the type T:
  - does not immediatelly create an item
  - - that way if type initialization is 'heavy' it is skipped for null items
  - uses 'alignas' to make sure it creates an array of unsigned char of the appropriate size and alignment of the desired type
  - once it needs to create an item T uses new but to allocate on the reseved stack slots rather than heap allocations

- main 'issue' with optional is having to nest its usage under a 'has_value' check
