/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   String[] validURLs = {"www.google.com",
			   				"http://www.google.com",
			   				"www.google.com:80",
			   				"www.google.com/$23",
			   				"www.google.com?action=view",
			   				"http://www.google.com:80",
			   				"http://www.google.com/$23",
			   				"http://www.google.com?action=view",
			   				"http://www.google.com",
			   				"ftp://www.google.com:80/$23/t123?action=view",
			   				"www.google.com:80/$23/t123?action=view",
			   				"http://www.google.com:80/$23/t123",
			   				"www.google.com:80/$23/t123",
			   				"http://www.google.com/$23/t123?action=view",
			   				"http://www.google.com?action=edit&mode=up",
			   				"http://www.google.com:80/$23/t123?action=view"
			   				};
	   
	   String[] invalidURLs = {"www.google.clax",
  							"htt://www.google.com",
  							"www.google.com:-80",
  							"www.google.com/../$23",
  							"www.google.com?action=view/#/",
  							"htp://www.google.com:80",
  							"http://1.2.3/$23",
  							"http:/256.256.256.256?action=view",
  							"http://?#.1.2.3",
  							"ftp://www.google.com:80/ $23/t123?action=view",
  							"www.google.com:80/$23/t123?=action=view",
  							"http://www.google:com:80/$23/t123",
  							"www.google.com:80:/$23/t123",
  							"http://www.google.com/$23?/t123?action=view"};
	   
	    System.out.print("The following URLs were incorrectly identified as invalid\n");   				
	   for(int i = 0 ;i<validURLs.length;i++)
	   {
		   if(!urlVal.isValid(validURLs[i])) {
			   System.out.println(validURLs[i]);
		   }
	   }
	   System.out.print("\nThe following URLs were incorrectly identified as valid\n");
	   for(int i = 0 ;i<invalidURLs.length;i++)
	   {
		   if(urlVal.isValid(invalidURLs[i])) {
			   System.out.println(invalidURLs[i]);
		   }
	   }
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
