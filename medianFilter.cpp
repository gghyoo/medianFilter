#include "Arduino.h"
#include "medianFilter.h"

MedianFilter::MedianFilter(int preFill) {
  memset(_buffer, _medianSize, preFill);
}

int MedianFilter::getFromBuffer(int r) {
  return _buffer[r];
}

int MedianFilter::getMedian() {
  return _buffer[halfSize];
}

int MedianFilter::filter(int newData) {
  if (newData < _buffer[halfSize]) {  // if less than median
    if (newData <= _buffer[0]) {        // if less than lowest reading
      memcpy(&_buffer[1], &_buffer[0], (_medianSize - 2) * 2);
      _buffer[0] = newData;
    }
    else {              // find insertion point from mid to low
      int q = halfSize - 1;
      while (newData < _buffer[q]) {
        q--;
      }
      int w = q;
      memcpy(&_buffer[q - 1], &_buffer[q], (_medianSize - 1 - q) * 2);
      _buffer[w] = newData;
    }
  }
  else {                                            // if above median
    if (newData >= _buffer[_medianSize - 1]) {        // if greater than highest reading
      for (int f = _medianSize - 2; f > 0; f--) {
        _buffer[f] = _buffer[f+1];
      }
      //memcpy(&_buffer[0],&_buffer[1], (_medianSize-2)*2); // cant get this to work, should replace above 3 lins
      _buffer[_medianSize - 1] = newData;
    }
    else {                                            // find insertion point from mid to high
      int q = halfSize;
      while (newData > _buffer[q]) {
        q++;
      }
      int w = q;
      for (int f = q; f < _medianSize - 2; f++) {
        _buffer[f + 1] = _buffer[f];
      }
      //memcpy(&_buffer[q],&_buffer[q+1], (_medianSize-2-q)*2); // cant get this to work
      _buffer[w] = newData;
    }
  }
  return _buffer[halfSize];
}

/* old version
  void MedianFilter::mySort(int newData){
  if (newData<=_buffer[0]){
    for (int q = 0; q<_medianSize-2; q++){
      _buffer[q+1] = _buffer[q];
    }
    _buffer[0] = newData;
  }
  else if (newData>=_buffer[_medianSize-1]){
    for (int q = _medianSize-1; q > 0; q--){
      _buffer[q-1] = _buffer[q];
    }
    _buffer[_medianSize-1] = newData;
  }
  else {
    int q = 1;
    while (newData > _buffer[q]){
      q++;
    }
    int w = q;
     for (; q<_medianSize-2; q++){
      _buffer[q+1] = _buffer[q];
    }
    _buffer[w] = newData;
  }
  }
*/

