int encrypt(char *password,int arrayToEncryptInt[20][20], /*int vertiBricks, int horiBricks,*/char *outputFileName)
{ 
  unsigned long rk[RKLENGTH(KEYBITS)];
  unsigned char key[KEYLENGTH(KEYBITS)];
  int i;
  int nrounds;
  FILE *output;
  
 // int vertiBricks=20;
  //int horiBricks=20;
  int totalBricks=400;
  //int vertiBricks16,horiBricks16;
  //vertiBricks16=13;
  char arrayToEncrypt[20][20];
  for(int i=0;i<20;i++)
  {
	  for(int j=0;j<20;j++)
	  {
		  arrayToEncrypt[i][j]=arrayToEncryptInt[i][j]+48;
	  }
  }

  char arrayToEncrypt16[25][16];
  int y16,j16;
  for(int v=0;v<20;v++)
  {
      for(int h=0;h<20;h++)
      {   y16=((v*20+h)/16);
          j16=(v*20+h)%16;
          arrayToEncrypt16[y16][j16]=arrayToEncrypt[v][h];
      }
  }        
  //for(int q= ((totalBricks-1)%16)+1;q<16;q++) arrayToEncrypt16[vertiBricks16-1][q]=' ';
  
  for (i = 0; i < sizeof(key); i++)
    key[i] = *password != 0 ? *password++ : 0;
  output = fopen(outputFileName, "wb");
  if (output == NULL)
  {//system("pause");
    fputs("File write error", stderr);
    return 1;
  }
  nrounds = rijndaelSetupEncrypt(rk, key, 256);
  for(int y=0;y<25;y++)
  {		//system("pause");
		unsigned char plaintext[16];
		unsigned char ciphertext[16];
		int j;
		for (j = 0; j < sizeof(plaintext); j++)
		{    
		  plaintext[j] = arrayToEncrypt16[y][j];
		}
	   
		rijndaelEncrypt(rk, nrounds, plaintext, ciphertext);
		if (fwrite(ciphertext, sizeof(ciphertext), 1, output) != 1)
		{
		  fclose(output);
		  fputs("File write error", stderr);
		  return 1;
		}
  }
  //system("pause");
  //fclose(unencryptedPlainText);
  fclose(output);
  return 1;
}