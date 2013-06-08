//
//  ControlGenerator.h
//  TonicDemo
//
//  Created by Morgan Packard on 2/12/13.

//


#ifndef __Tonic_ControlGenerator__
#define __Tonic_ControlGenerator__

#include "BaseGenerator.h"

namespace Tonic {
  
  struct ControlGeneratorOutput{
    
    TonicFloat  value;
    bool        triggered;
    
    ControlGeneratorOutput() : value(0), triggered(false) {};
  };

  namespace Tonic_{

    class ControlGenerator_ : public BaseGenerator_ {
      
      public:
      
        ControlGenerator_ * copy() { return NULL; }
      
        // Only override tick if you need custom reuse behavior
        // Pass in a pointer to a TonicFloat to return a value. Some generators may not care about value.
        virtual ControlGeneratorOutput tick( const TonicContext_ & context );
        
        // Used for initializing other generators (see smoothed() method for example)
        virtual ControlGeneratorOutput initialOutput();
        
      protected:
        
        ControlGeneratorOutput  output_;
        
      };
      
      inline ControlGeneratorOutput ControlGenerator_::tick(const TonicContext_ & context){
        
        if (context.forceNewOutput || lastFrameIndex_ != context.elapsedFrames){
          lastFrameIndex_ = context.elapsedFrames;
          computeOutput(context);
        }
        
#ifdef TONIC_DEBUG
      if(output_.value != output_.value){
        Tonic::error("ControlGenerator_::tick NaN detected.", true);
      }
#endif
      
      return output_;

    }

  }

  // forward declaration
  class RampedValue;

  class ControlGenerator : public BaseGenerator
  {

    public:
      
      ControlGenerator(Tonic_::ControlGenerator_ * cGen = NULL) : BaseGenerator(cGen) {}
      
      inline ControlGeneratorOutput tick( const Tonic_::TonicContext_ & context ){
        return static_cast<Tonic_::ControlGenerator_*>(obj)->tick(context);
      }
      
      // shortcut for creating ramped value
      RampedValue smoothed(float length = 0.05);
    
  };

  
  template<class GenType>
  class TemplatedControlGenerator : public ControlGenerator{
  protected:
    GenType* gen(){
      return static_cast<GenType*>(obj);
    }

    public:
      TemplatedControlGenerator() : ControlGenerator(new GenType) {}
    
  };

  
}

#include "ControlValue.h"

#define TONIC_CONTROL_GENERATOR_SETTERS(generatorClassName, methodNameInGenerator, methodNameInGenerator_)\
\
generatorClassName& methodNameInGenerator(float arg){                              \
return methodNameInGenerator( ControlValue(arg) );                                 \
}                                                                                  \
\
generatorClassName& methodNameInGenerator(ControlGenerator arg){                   \
this->gen()->methodNameInGenerator_(arg);                                          \
return static_cast<generatorClassName&>(*this);                                    \
} \


#endif
