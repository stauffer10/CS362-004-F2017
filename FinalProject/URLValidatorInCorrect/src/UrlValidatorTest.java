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
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   
   }
   
public void testYourFirstPartition(){

	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	/****
	* consider the five parts of URL - scheme, authority, port, path, query as
	* [valid/invalid/absent, valid/invalid/absent, valid/invalid/absent, valid/invalid/absent, valid/invalid/absent]
	* an example assertion may be [valid, valid, valid, valid, invalid]
	****/

	//first try valid URL's
	//[valid, valid, valid, valid, valid]
	assertTrue(urlVal.isValid("http://www.google.com:65535/test1?action=view"));
	assertTrue(urlVal.isValid("http://afterzmusic.com:80/about/?action=edit&mode=up")); 	

	//[absent, valid, valid, valid, valid]
	assertTrue(urlVal.isValid("www.google.com:65535/test1?action=view"));
	assertTrue(urlVal.isValid("afterzmusic.com:80/about/?action=edit&mode=up")); 

	//[valid, valid, absent, valid, valid]
	assertTrue(urlVal.isValid("http://www.google.com/test1?action=view"));
	assertTrue(urlVal.isValid("http://afterzmusic.com/about/?action=edit&mode=up")); 

	//[valid, valid, valid, absent, valid]
	assertTrue(urlVal.isValid("http://www.google.com:65535?action=view"));
	assertTrue(urlVal.isValid("http://afterzmusic.com:80?action=edit&mode=up")); 

	//[valid, valid, valid, valid, absent]
	assertTrue(urlVal.isValid("http://www.google.com:65535/test1"));
	assertTrue(urlVal.isValid("http://afterzmusic.com:80/about/")); 

	//[absent, valid, absent, valid, absent]
	assertTrue(urlVal.isValid("www.google.com/test1"));
	assertTrue(urlVal.isValid("afterzmusic.com/about/")); 

	//[valid, valid, absent, absent, absent]
	assertTrue(urlVal.isValid("http://www.google.com"));
	assertTrue(urlVal.isValid("http://afterzmusic.com")); 

	//try invalid URL's by testing one invalid section at a time
	//[invalid, valid, valid, valid, valid]
	assertFalse(urlVal.isValid("http:www.google.com:65535/test1?action=view"));
	assertFalse(urlVal.isValid("://afterzmusic.com:80/about/?action=edit&mode=up")); 	

	//[valid, invalid, valid, valid, valid]
	assertFalse(urlVal.isValid("http://1.2.3:65535/test1?action=view"));
	assertFalse(urlVal.isValid("http://afterz:80/about/?action=edit&mode=up")); 

	//[valid, valid, invalid, valid, valid]
	assertFalse(urlVal.isValid("http://www.google.com:-1/test1?action=view"));
	assertFalse(urlVal.isValid("http://afterzmusic.com:ZZ/about/?action=edit&mode=up")); 

	//[valid, valid, valid, invalid, valid]
	assertFalse(urlVal.isValid("http://www.google.com:65535/../?action=view"));
	assertFalse(urlVal.isValid("http://afterzmusic.com:80/about//file?action=edit&mode=up")); 

	//[valid, valid, valid, valid, invalid]
	assertFalse(urlVal.isValid("http://www.google.com:65535/test1?action=&"));
	assertFalse(urlVal.isValid("http://afterzmusic.com:80/about/?edit&mode=up")); 

	//[absent, invalid, absent, absent, absent]
	assertFalse(urlVal.isValid("1.2.3"));
	assertFalse(urlVal.isValid("afterz")); 
	
	//[absent, valid, absent, invalid, absent]
	assertFalse(urlVal.isValid("www.google.com/../"));
	assertFalse(urlVal.isValid("afterzmusic.com/about//file")); 

	//[valid, absent, valid, valid, valid]
	assertFalse(urlVal.isValid("http://:65535/test1?action=view"));
	assertFalse(urlVal.isValid("http://:80/about/?action=edit&mode=up")); 

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
