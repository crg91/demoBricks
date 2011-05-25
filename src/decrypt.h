int decrypt(char *password,int decryptedArrayInt[20][20],char* inputFileName/*,const int dimension*/)
{	string x=password;
	char decryptedArray[20][20];
//	int dimension=20;
//int   decryptedArrayKnownSize=dimension*dimension;
  //int rowNumber=25;
   char decryptedArray16[25][16];
  unsigned long rk[RKLENGTH(KEYBITS)];
  unsigned char key[KEYLENGTH(KEYBITS)];
  int i;
  int nrounds;
  FILE *input;
  FILE *decryptedPlainText;///
  decryptedPlainText=fopen("outputFile_temp.txt","wb");
  if (decryptedPlainText == NULL)
  {
    fputs("File write error", stderr);
	cout<<"file write errror";
	system("pause");
    return 1;
  }
  for (i = 0; i < sizeof(key); i++)
    key[i] = *password != 0 ? *password++ : 0;
  input = fopen(/*argv[2]*/inputFileName, "rb");
  if (input == NULL)
  {  
    fputs("File read error", stderr);
	cout<<"file read error";
	system("pause");
    return 1;
  }
  nrounds = rijndaelSetupDecrypt(rk, key, 256);
  //int x=0,y=0;//temp=0;
  //while (1)
for(int y=0;y<25;y++)
  {//system("pause");
    unsigned char plaintext[16];
    unsigned char ciphertext[16];
    //int j;
    if (fread(ciphertext, sizeof(ciphertext), 1, input) != 1)
      break;
    rijndaelDecrypt(rk, nrounds, ciphertext, plaintext);
    //decryptedArray16=plaintext;
    fwrite(plaintext, sizeof(plaintext), 1, /*stdout*/decryptedPlainText);
        for(int x=0; x<16 ;x++)
        {
			//if((16*y+x+1)>decryptedArrayKnownSize){ break; }
        decryptedArray16[y][x]=plaintext[x];
        }
        //y++;
  }//end of while
  int tempx,tempy,breaking=0;
  for(int i=0;i<25;i++)
  {
     for(int j=0;j<16;j++)
     {
         tempy=(16*i+j)/dimension;
         tempx=(16*i+j)%dimension;
         decryptedArray[tempy][tempx]=decryptedArray16[i][j];
         /*if(tempy==(dimension-1)&&tempx==(dimension-1))
         {
                  break;
                  breaking=1;
         } */   
     }//if (breaking==1) break;
 }        

  for(int i=0;i<20;i++)
  {
     for(int j=0;j<20;j++)
     {
		 decryptedArrayInt[i][j]=decryptedArray[i][j]-48;
     }
 }
	//cout<<"password "<<x<<"yeah"<<endl;
  string pwd=" ";
  pwd=x;
  pwd.append(".jek");
  //cout<<"pwd "<<pwd<<" length "<<pwd.length();
  //sytem("pause");
  if(pwd!=inputFileName)
  {		cout<<"fish...";	//system("pause");
	  for(int i=0;i<20;i++)
	  {
		 for(int j=0;j<20;j++)
		 {
			 decryptedArrayInt[i][j]=2;
		 }
	  }
	
  }

  fclose(decryptedPlainText);///
  fclose(input);
  return 1;
}