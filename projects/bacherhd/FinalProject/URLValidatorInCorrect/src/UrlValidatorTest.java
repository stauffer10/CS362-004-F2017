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
import java.util.Random;

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
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
	   ResultPair pair;
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   boolean result;
	   
	   for(int i = 0;i<9000000;i++)
	   {
		   pair = this.generateRandomUrl();
		   if (pair.valid) {
			   result = urlVal.isValid(pair.item);
			   assertEquals(result, pair.valid);
			   /*
			   if (pair.valid != result) {
				   System.out.println("ERROR: " + pair.item + " : Expected " + String.valueOf(pair.valid)
				   + ", but got " + String.valueOf(result));
			   } else {
				   System.out.println("OK   : " + pair.item + " : " + String.valueOf(pair.valid));
			   } 
			   */
		   }
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   
   
   private ResultPair generateRandomUrl()
   {
	   String url = "";
	   boolean valid = true;
	   int j = 0;
	   
	   /* select a protocol and append a delimiter if non-empty */
	   ResultPair protoPair = this.protocol[this.rand.nextInt(this.protocol.length)];
	   valid &= protoPair.valid;
	   
	   if (protoPair.item != "") {
		   url += protoPair.item;
		   j = this.rand.nextInt(this.protocolJoinStr.length);
		   url += this.protocolJoinStr[j].item;
		   valid &= protoPair.valid & this.protocolJoinStr[j].valid;
	   }
	   
	   ResultPair authPair = this.auth[this.rand.nextInt(this.auth.length)];
	   valid &= authPair.valid;
	   url += authPair.item;
	   
	   /* select a subdomain and append a delimiter if non-empty */
	   ResultPair subDomainPair = this.subDomain[this.rand.nextInt(this.subDomain.length)];
	   valid &= subDomainPair.valid;
	   
	   if (subDomainPair.item != "") {
		   url += subDomainPair.item;
		   j = this.rand.nextInt(this.domainJoinStr.length);
		   url += this.domainJoinStr[j].item;
		   valid &= this.domainJoinStr[j].valid;
	   }
	   
	   
	   ResultPair domainPair = this.domain[this.rand.nextInt(this.domain.length)];
	   valid &= domainPair.valid;
	   
	   if (domainPair.item != "") {
		   url += domainPair.item;
		   j = this.rand.nextInt(this.domainJoinStr.length);
		   url += this.domainJoinStr[j].item;
		   valid &= this.domainJoinStr[j].valid;
	   }
	   
	   ResultPair tldPair = this.tld[this.rand.nextInt(this.tld.length)];
	   url += tldPair.item;
	   valid &= tldPair.valid;
	   
	   ResultPair portPair = this.portSpecifier[this.rand.nextInt(this.portSpecifier.length)];
	   url += portPair.item;
	   valid &= portPair.valid;
	   
	   
	   ResultPair pathPair = this.path[this.rand.nextInt(this.path.length)];
	   valid &= pathPair.valid;
	   if (pathPair.item != "") {
		   j = this.rand.nextInt(this.pathJoinStr.length);
		   valid &= this.pathJoinStr[j].valid;
		   url += this.pathJoinStr[j].item;
		   url += pathPair.item;
	   }
	   
	   ResultPair filePair = this.file[this.rand.nextInt(this.file.length)];
	   valid &= filePair.valid;
	   if (filePair.item != "") {
		   j = this.rand.nextInt(this.pathJoinStr.length);
		   valid &= this.pathJoinStr[j].valid;
		   url += this.pathJoinStr[j].item;
		   url += filePair.item;
	   }
	   
	   ResultPair queryPair = this.query[this.rand.nextInt(this.query.length)];
	   valid &= queryPair.valid;
	   url += queryPair.item;
	   
	   
	   ResultPair fragPair = this.fragment[this.rand.nextInt(this.fragment.length)];
	   valid  &= fragPair.valid;
	   url += fragPair.item;
	   
	   return new ResultPair(url, valid);
   }
   
   private Random rand = new Random(System.currentTimeMillis());
   
   
   private ResultPair[] protocol = {
		   new ResultPair("http", true),
		   new ResultPair("ftp",  true),
		   new ResultPair("https", true),
		   new ResultPair("ptth", false),
		   new ResultPair("zombo", false),
		   new ResultPair("", true)
   };
   
   private ResultPair[] protocolJoinStr = {
		   new ResultPair("://", true),
		   new ResultPair("", false),
		   new ResultPair(":", false),
		   new ResultPair("/", false),
		   new ResultPair(":/", false),
		   new ResultPair("//", false)
   };
		   
   private ResultPair[] domain = {
		   new ResultPair("google", true),
		   new ResultPair("amazon", true),
		   new ResultPair("facebook", false),
		   new ResultPair("..", false),
		   new ResultPair(".", false),
		   new ResultPair("", false)
   };
   
   private ResultPair[] tld = {
		   new ResultPair("com", true),
		   new ResultPair("biz", true),
		   new ResultPair("", false),
		   new ResultPair("info", true),
		   new ResultPair("aaaaa", false)
   };
   
   private ResultPair[] subDomain = {
		   new ResultPair("www", true),
		   new ResultPair("img", true),
		   new ResultPair("", true),
		   new ResultPair(".", false)
   };
   
   private ResultPair[] domainJoinStr = {
		   new ResultPair(".", true),
		   new ResultPair("", false),
		   new ResultPair(";", false)
   };
   
   private ResultPair[] path = {
		   new ResultPair("images", true),
		   new ResultPair("members", true),
		   new ResultPair("forum", true),
		   new ResultPair("images/members/forum", true),
		   new ResultPair("images//members//forum", false),
		   new ResultPair("", true),
		   new ResultPair("//", false) 
   };
   
   private ResultPair[] pathJoinStr = {
		   new ResultPair("/", true),
		   new ResultPair("//", false),
		   new ResultPair("\\", false),
		   new ResultPair("#", false)
   };
   
   private ResultPair[] file = {
		   new ResultPair("somefile", true),
		   new ResultPair("image1.png", true),
		   new ResultPair("az09-._~", true),
		   new ResultPair("archive.zip", true),
		   new ResultPair("", true)
   };
   
   private ResultPair[] portSpecifier = {
		   new ResultPair(":80", true),
		   new ResultPair(":", false),
		   new ResultPair(":notaport", false),
		   new ResultPair(":443", true),
		   new ResultPair(":?", false),
		   new ResultPair("", true)
   };
   
   private ResultPair[] auth = {
		   new ResultPair("user@", true),
		   new ResultPair("user:pass@", true),
		   new ResultPair(":pass@", false),
		   new ResultPair("@", false)
   };
   
   private ResultPair[] query = {
		   new ResultPair("", true),
		   new ResultPair("?t=60", true),
		   new ResultPair("&t=60", false),
		   new ResultPair("?t=60&p=50&q=99", true)
   };
   
   private ResultPair[] fragment = {
		   new ResultPair("", true),
		   new ResultPair("#", true),
		   new ResultPair("#somefrag", true),
		   new ResultPair("#frag%20with%20spaces", true),
		   new ResultPair("#frag+with+spaces", true)
   };
}
