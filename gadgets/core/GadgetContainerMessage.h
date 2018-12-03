#pragma once

#include <string>
#include "Message.h"

namespace Gadgetron {


    class ACE_Message_Block {

    public:
        ACE_Message_Block(){};
        ACE_Message_Block(const std::string &s) : buffer(s) {

        }

        [[deprecated]]
        const char *rd_ptr() { return buffer.c_str(); };

        virtual ~ACE_Message_Block() {
            if (cont_element){
                cont_element->release();
            }
        };

        virtual void *release() {
            delete (this); // Seppuku
            return nullptr;
        }

        ACE_Message_Block* cont(){return cont_element;}
        void  cont(ACE_Message_Block* ptr){cont_element = ptr;}


        private:
        ACE_Message_Block* cont_element;

    private:
        std::string buffer;
    };


    class GadgetContainerMessageBase : public ACE_Message_Block {
    public:


        virtual std::unique_ptr<Core::Message> take_message() = 0;

        virtual ~GadgetContainerMessageBase(){};
    };



    template<class T>
    class GadgetContainerMessage : public GadgetContainerMessageBase {

    public:
        /**
         *  Constructor, passing on input arguments to the contained class.
         * @param xs Variadic arguments to the contained class
         */

        template<typename... X>
        GadgetContainerMessage(X&&... xs) : data(std::make_unique<T>(std::move(xs)...))  {

        }

        virtual ~GadgetContainerMessage() {

        }

        virtual std::unique_ptr<Core::Message> take_message() override {
            return std::make_unique<Core::TypedMessage<T>>(std::move(data));
        }

        T *getObjectPtr() {
            return data.get();
        }

        GadgetContainerMessage<T>* duplicate() {
            return new GadgetContainerMessage<T>(*this->data);
        }

    private:

        std::unique_ptr<T> data;
    };


    template<class T>
    GadgetContainerMessage<T> *AsContainerMessage(ACE_Message_Block *mb) {
        if (typeid(mb) == typeid(GadgetContainerMessage<T> *))
            return reinterpret_cast<GadgetContainerMessage<T> * >(mb);
        return nullptr;
    }
}
