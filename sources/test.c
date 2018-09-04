int main()
{ 
  char *addr; 

	addr = malloc(7);
	strcpy(addr, "salut\n");
  allocation_dump("wtf");
  return (0); 
}