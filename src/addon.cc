#include <node.h>
#include <nan.h>
#include <iostream>

// Data model
#include "datamodel/EventInfo.h"
#include "datamodel/EventInfoCollection.h"
#include "datamodel/Particle.h"
#include "datamodel/ParticleCollection.h"

// ROOT
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

// STL
#include <iostream>
#include <vector>

// albers specific includes
#include "albers/EventStore.h"
#include "albers/Registry.h"
#include "albers/Writer.h"

#include "../deps/examples/write.cc"

struct Price{
    double euro;
    double dollar;
};

struct Product {
  double weight;
  Price price;
};

Product setProduct(Product product, double weight, double dollar, double euro){
    product.weight = weight;
    product.price.dollar = dollar;
    product.price.euro = euro;

    return product;
}

Product getProduct(int id) {

    Product product;
    if (id==1){
        product = setProduct(product, 1, 1.1, 1.1);
        std::cout << "id = 1" << std::endl;
    }else{
        product.weight=999;
        product.price.euro=999.99;
        product.price.dollar=999.88;
        std::cout << "id unknown" << std::endl;
    }

    return product;
}

int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return(n);
}

NAN_METHOD(getProductAdapter) {
  NanScope();
  v8::Local<v8::Object> results = NanNew<v8::Object>();
  Product answer = getProduct(args[0]->Uint32Value());
    results->Set(NanNew<v8::String>("weight"), NanNew<v8::Number>(answer.weight));
    results->Set(NanNew<v8::String>("euroPrice"), NanNew<v8::Number>(answer.price.euro));
    results->Set(NanNew<v8::String>("dollarPrice"), NanNew<v8::Number>(answer.price.dollar));

    NanReturnValue(results);
}

NAN_METHOD(getFactorial) {
  NanScope();
  int answer = factorial(args[0]->Uint32Value());
  NanReturnValue(NanNew<v8::Number>(answer));
}

void writeMain(){
  // gSystem->Load("libDataModelExample.so");

  std::cout<<"start processing"<<std::endl;

  albers::Registry   registry;
  albers::EventStore store(&registry);
  albers::Writer     writer("example.root", &registry);

  unsigned nevents=10000;

  EventInfoCollection& evinfocoll = store.create<EventInfoCollection>("EventInfo");
  writer.registerForWrite<EventInfoCollection>("EventInfo");

  for(unsigned i=0; i<nevents; ++i) {
    processEvent(i, store, writer);
  }

  writer.finish();
}

NAN_METHOD(writeExamples) {
    NanScope();
    writeMain();
    NanReturnUndefined();
}

void Init(v8::Handle<v8::Object> target) {
    target->Set(
          NanNew<v8::String>("getFactorial")
        , NanNew<v8::FunctionTemplate>(getFactorial)->GetFunction()
      );
      target->Set(
          NanNew<v8::String>("getProduct")
          , NanNew<v8::FunctionTemplate>(getProductAdapter)->GetFunction()
      );
      target->Set(
          NanNew<v8::String>("writeExamples")
          , NanNew<v8::FunctionTemplate>(writeExamples)->GetFunction()
      );
}

NODE_MODULE(addon, Init)