  �@  /* cat.c */     #include <stdio.h>     main (argc, argv)  	int	argc; 	 char	**argv;  {      FILE	*fp, *fopen();     ,    if(argc == 1) /* no args; copy std in */ ,     	filecopy(stdin);      else      	while (--argc > 0)  2    	    if ((fp = fopen(*++argv, "r")) == NULL) { 2 6    		fprintf(stderr, "list: can't open %s\n", *argv); 6     		    exit(1);      	    } else {      		filecopy(fp);      		fclose(fp);  
    	    } 
     exit(0);  }     *filecopy(fp)	/* copy file fp to std out */ * 	FILE	*fp; 	 {  
    int	c; 
    !    while ((c = getc(fp)) != EOF) !     	putc(c, stdout);  } � �                                                                                                                            