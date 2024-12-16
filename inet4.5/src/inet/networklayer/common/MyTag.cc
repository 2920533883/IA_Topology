//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "MyTag.h"

namespace inet {
MyTag::MyTag() {
    // TODO Auto-generated constructor stub

}

MyTag::~MyTag() {
    // TODO Auto-generated destructor stub
}
void MyTag::setAddress(MacAddress src, MacAddress dest){
    srcAddress = src;
    destAddress = dest;
}
void MyTag::setSrcAddress(MacAddress add){
    srcAddress = add;
}
void MyTag::setDestAddress(MacAddress add){
    destAddress = add;
}
MacAddress MyTag::getSrcAddress(){
    return srcAddress;
}
MacAddress MyTag::getDestAddress(){
    return destAddress;
}
} /* namespace inet */
