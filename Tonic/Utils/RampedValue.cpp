//
//  RampedValue.cpp
//  Tonic
//
//  Created by Virek on 2/7/13.
//  Copyright (c) 2013 Morgan Packard. All rights reserved.
//

#include "RampedValue.h"

namespace Tonic { namespace Tonic_{
  
  RampedValue_::RampedValue_() :
    finished_(true),
    count_(0),
    defLen_(2205),
    len_(2205),
    target_(0),
    last_(0),
    inc_(0)
  {
    
  }
  
  RampedValue_::~RampedValue_(){
    
  }

} // Namespace Tonic_
  
  RampedValue & RampedValue::defLenMs(TonicFloat defLenMs){
    gen()->setDefaultLength( defLenMs*Tonic::sampleRate()/1000.0f );
    return  *this;
  }
  
  RampedValue & RampedValue::defValue(TonicFloat defValue){
    gen()->setValue(defValue);
    return *this;
  }
  
  void RampedValue::setTarget(TonicFloat target, TonicFloat lenMs){
    unsigned long length = lenMs > 0 ? lenMs*Tonic::sampleRate()/1000.0f : 0;
    gen()->setTarget(target, length);
  }
  
  void RampedValue::setValue(TonicFloat value){
    gen()->setValue(value);
  }
  
} // Namespace Tonic
