/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2001 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Id$
 * $Log$
 * Revision 1.1  2001/09/25 15:58:45  peiyongz
 * DTV Reorganization: new class
 *
 */

// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <validators/datatype/NCNameDatatypeValidator.hpp>
#include <validators/datatype/InvalidDatatypeValueException.hpp>

// ---------------------------------------------------------------------------
//  Constructors and Destructor
// ---------------------------------------------------------------------------
NCNameDatatypeValidator::NCNameDatatypeValidator()
:StringDatatypeValidator()
{
    DatatypeValidator::setType(DatatypeValidator::NCName);
}

NCNameDatatypeValidator::~NCNameDatatypeValidator()
{}

NCNameDatatypeValidator::NCNameDatatypeValidator(
                          DatatypeValidator*            const baseValidator
                        , RefHashTableOf<KVStringPair>* const facets
                        , RefVectorOf<XMLCh>*           const enums
                        , const int                           finalSet)
:StringDatatypeValidator(baseValidator, facets, enums, finalSet)
{
    //
    // the StringDatatypeValidator has the same set of
    // constrainning facets as the NCNameDatatypeValidator
    // and the StringDatatypeValidator(...) would do
    // all the jobs there.

    //
    // if enumeration is provided, make sure that they
    // are all valid NCName(s).
    //
    if (enums)
    {
        int enumLength = enums->size();
        for ( int i = 0; i < enumLength; i++)
        {
            checkValueSpace(enums->elementAt(i));
        }
    }

    DatatypeValidator::setType(DatatypeValidator::NCName);

}

// -----------------------------------------------------------------------
// Compare methods
// -----------------------------------------------------------------------
int NCNameDatatypeValidator::compare(const XMLCh* const lValue
                                   , const XMLCh* const rValue)
{
    return ( XMLString::compareString(lValue, rValue)==0 ? 0 : -1);
}

DatatypeValidator* NCNameDatatypeValidator::newInstance(
                                      RefHashTableOf<KVStringPair>* const facets
                                    , RefVectorOf<XMLCh>*           const enums
                                    , const int                           finalSet)
{
    return (DatatypeValidator*) new NCNameDatatypeValidator(this, facets, enums, finalSet);
}

void NCNameDatatypeValidator::validate(const XMLCh* const content)
{
    // use StringDatatypeValidator (which in turn, invoke
    // the baseValidator) to validate content against
    // facets if any.
    //
    StringDatatypeValidator::validate(content);

    checkValueSpace(content);

    return;
}

void NCNameDatatypeValidator::checkValueSpace(const XMLCh* const content)
{
    //
    // 3.3.7 check must: "NCName"
    //
    if ( !XMLString::isValidNCName(content))
    {
        ThrowXML1(InvalidDatatypeValueException
                , XMLExcepts::VALUE_Invalid_NCName
                , content);
    }

}

 /**
  * End of file NCNameDatatypeValidator.cpp
  */
