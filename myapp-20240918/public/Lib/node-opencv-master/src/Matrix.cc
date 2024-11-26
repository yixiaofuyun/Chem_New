#include "Contours.h"
#include "Matrix.h"
#include "OpenCV.h"
#include <string.h>
#include <nan.h>

#if CV_MAJOR_VERSION >= 4
#include <opencv2/imgproc/types_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#endif

Nan::Persistent<FunctionTemplate> Matrix::constructor;

cv::Scalar setColor(Local<Object> objColor);
cv::Point setPoint(Local<Object> objPoint);
cv::Rect* setRect(Local<Object> objRect, cv::Rect &result);

void Matrix::Init(Local<Object> target) {
  Nan::HandleScope scope;

  //Class
  Local<FunctionTemplate> ctor = Nan::New<FunctionTemplate>(Matrix::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Matrix").ToLocalChecked());

  // Prototype
  Nan::SetPrototypeMethod(ctor, "copyMakeBorder", CopyMakeBorder);
  Nan::SetPrototypeMethod(ctor, "row", Row);
  Nan::SetPrototypeMethod(ctor, "col", Col);
  Nan::SetPrototypeMethod(ctor, "pixelRow", PixelRow);
  Nan::SetPrototypeMethod(ctor, "pixelCol", PixelCol);
  Nan::SetPrototypeMethod(ctor, "empty", Empty);
  Nan::SetPrototypeMethod(ctor, "get", Get);
  Nan::SetPrototypeMethod(ctor, "getPixel", GetPixel);
  Nan::SetPrototypeMethod(ctor, "set", Set);
  Nan::SetPrototypeMethod(ctor, "put", Put);
  Nan::SetPrototypeMethod(ctor, "brightness", Brightness);
  Nan::SetPrototypeMethod(ctor, "normalize", Normalize);
  Nan::SetPrototypeMethod(ctor, "norm", Norm);
  Nan::SetPrototypeMethod(ctor, "getData", GetData);
  Nan::SetPrototypeMethod(ctor, "pixel", Pixel);
  Nan::SetPrototypeMethod(ctor, "width", Width);
  Nan::SetPrototypeMethod(ctor, "height", Height);
  Nan::SetPrototypeMethod(ctor, "type", Type);
  Nan::SetPrototypeMethod(ctor, "size", Size);
  Nan::SetPrototypeMethod(ctor, "clone", Clone);
  Nan::SetPrototypeMethod(ctor, "crop", Crop);
  Nan::SetPrototypeMethod(ctor, "toBuffer", ToBuffer);
  Nan::SetPrototypeMethod(ctor, "toBufferAsync", ToBufferAsync);
  Nan::SetPrototypeMethod(ctor, "ellipse", Ellipse);
  Nan::SetPrototypeMethod(ctor, "rectangle", Rectangle);
  Nan::SetPrototypeMethod(ctor, "line", Line);
  Nan::SetPrototypeMethod(ctor, "fillPoly", FillPoly);
  Nan::SetPrototypeMethod(ctor, "save", Save);
  Nan::SetPrototypeMethod(ctor, "saveAsync", SaveAsync);
  Nan::SetPrototypeMethod(ctor, "resize", Resize);
  Nan::SetPrototypeMethod(ctor, "rotate", Rotate);
  Nan::SetPrototypeMethod(ctor, "warpAffine", WarpAffine);
  Nan::SetPrototypeMethod(ctor, "copyTo", CopyTo);
  Nan::SetPrototypeMethod(ctor, "convertTo", ConvertTo);
  Nan::SetPrototypeMethod(ctor, "pyrDown", PyrDown);
  Nan::SetPrototypeMethod(ctor, "pyrUp", PyrUp);
  Nan::SetPrototypeMethod(ctor, "channels", Channels);
  Nan::SetPrototypeMethod(ctor, "convertGrayscale", ConvertGrayscale);
  Nan::SetPrototypeMethod(ctor, "convertHSVscale", ConvertHSVscale);
  Nan::SetPrototypeMethod(ctor, "gaussianBlur", GaussianBlur);
  Nan::SetPrototypeMethod(ctor, "medianBlur", MedianBlur);
  Nan::SetPrototypeMethod(ctor, "bilateralFilter", BilateralFilter);
  Nan::SetPrototypeMethod(ctor, "sobel", Sobel);
  Nan::SetPrototypeMethod(ctor, "copy", Copy);
  Nan::SetPrototypeMethod(ctor, "flip", Flip);
  Nan::SetPrototypeMethod(ctor, "roi", ROI);
  Nan::SetPrototypeMethod(ctor, "ptr", Ptr);
  Nan::SetPrototypeMethod(ctor, "absDiff", AbsDiff);
  Nan::SetPrototypeMethod(ctor, "dct", Dct);
  Nan::SetPrototypeMethod(ctor, "idct", Idct);
  Nan::SetPrototypeMethod(ctor, "addWeighted", AddWeighted);
  Nan::SetPrototypeMethod(ctor, "add", Add);
  Nan::SetPrototypeMethod(ctor, "bitwiseXor", BitwiseXor);
  Nan::SetPrototypeMethod(ctor, "bitwiseNot", BitwiseNot);
  Nan::SetPrototypeMethod(ctor, "bitwiseAnd", BitwiseAnd);
  Nan::SetPrototypeMethod(ctor, "countNonZero", CountNonZero);
  Nan::SetPrototypeMethod(ctor, "moments", Moments);
  Nan::SetPrototypeMethod(ctor, "canny", Canny);
  Nan::SetPrototypeMethod(ctor, "dilate", Dilate);
  Nan::SetPrototypeMethod(ctor, "erode", Erode);
  Nan::SetPrototypeMethod(ctor, "findContours", FindContours);
  Nan::SetPrototypeMethod(ctor, "drawContour", DrawContour);
  Nan::SetPrototypeMethod(ctor, "drawAllContours", DrawAllContours);
  Nan::SetPrototypeMethod(ctor, "goodFeaturesToTrack", GoodFeaturesToTrack);
  #ifdef HAVE_OPENCV_VIDEO
  Nan::SetPrototypeMethod(ctor, "calcOpticalFlowPyrLK", CalcOpticalFlowPyrLK);
  #endif
  Nan::SetPrototypeMethod(ctor, "houghLinesP", HoughLinesP);
  Nan::SetPrototypeMethod(ctor, "houghCircles", HoughCircles);
  Nan::SetPrototypeMethod(ctor, "inRange", inRange);
  Nan::SetPrototypeMethod(ctor, "adjustROI", AdjustROI);
  Nan::SetPrototypeMethod(ctor, "locateROI", LocateROI);
  Nan::SetPrototypeMethod(ctor, "threshold", Threshold);
  Nan::SetPrototypeMethod(ctor, "adaptiveThreshold", AdaptiveThreshold);
  Nan::SetPrototypeMethod(ctor, "meanStdDev", MeanStdDev);
  Nan::SetPrototypeMethod(ctor, "cvtColor", CvtColor);
  Nan::SetPrototypeMethod(ctor, "split", Split);
  Nan::SetPrototypeMethod(ctor, "merge", Merge);
  Nan::SetPrototypeMethod(ctor, "equalizeHist", EqualizeHist);
  Nan::SetPrototypeMethod(ctor, "floodFill", FloodFill);
  Nan::SetPrototypeMethod(ctor, "matchTemplate", MatchTemplate);
  Nan::SetPrototypeMethod(ctor, "matchTemplateByMatrix", MatchTemplateByMatrix);
  Nan::SetPrototypeMethod(ctor, "templateMatches", TemplateMatches);
  Nan::SetPrototypeMethod(ctor, "minMaxLoc", MinMaxLoc);
  Nan::SetPrototypeMethod(ctor, "pushBack", PushBack);
  Nan::SetPrototypeMethod(ctor, "putText", PutText);
  Nan::SetPrototypeMethod(ctor, "getPerspectiveTransform", GetPerspectiveTransform);
  Nan::SetPrototypeMethod(ctor, "warpPerspective", WarpPerspective);
  Nan::SetMethod(ctor, "Zeros", Zeros);
  Nan::SetMethod(ctor, "Ones", Ones);
  Nan::SetMethod(ctor, "Eye", Eye);
  Nan::SetMethod(ctor, "getRotationMatrix2D", GetRotationMatrix2D);
  Nan::SetPrototypeMethod(ctor, "copyWithMask", CopyWithMask);
  Nan::SetPrototypeMethod(ctor, "setWithMask", SetWithMask);
  Nan::SetPrototypeMethod(ctor, "meanWithMask", MeanWithMask);
  Nan::SetPrototypeMethod(ctor, "mean", Mean);
  Nan::SetPrototypeMethod(ctor, "shift", Shift);
  Nan::SetPrototypeMethod(ctor, "reshape", Reshape);
// leave this out - can't see a way it could be useful to us, as release() always completely forgets the data
//  Nan::SetPrototypeMethod(ctor, "addref", Addref);
  Nan::SetPrototypeMethod(ctor, "release", Release);
  Nan::SetPrototypeMethod(ctor, "getrefCount", GetrefCount);
  Nan::SetPrototypeMethod(ctor, "subtract", Subtract);
  Nan::SetPrototypeMethod(ctor, "compare", Compare);
  Nan::SetPrototypeMethod(ctor, "mul", Mul);
  Nan::SetPrototypeMethod(ctor, "div", Div);
  Nan::SetPrototypeMethod(ctor, "pow", Pow);

  Nan::Set(target, Nan::New("Matrix").ToLocalChecked(), ctor->GetFunction( Nan::GetCurrentContext() ).ToLocalChecked());
};

NAN_METHOD(Matrix::New) {
  Nan::HandleScope scope;
  if (info.This()->InternalFieldCount() == 0) {
    Nan::ThrowTypeError("Cannot instantiate without new");
  }

  Matrix *mat;

  if (info.Length() == 0) {
    mat = new Matrix;
  } else if (info.Length() == 2 && info[0]->IsInt32() && info[1]->IsInt32()) {
    mat = new Matrix(Nan::To<int>(info[0]).FromJust(), Nan::To<int>(info[1]).FromJust());
  } else if (info.Length() == 3 && info[0]->IsInt32() && info[1]->IsInt32()
      && info[2]->IsInt32()) {
    mat = new Matrix(Nan::To<int>(info[0]).FromJust(), Nan::To<int>(info[1]).FromJust(),
        info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked());
  } else if (info.Length() == 4 && info[0]->IsInt32() && info[1]->IsInt32() &&
        info[2]->IsInt32() && info[3]->IsArray()) {
    mat = new Matrix(Nan::To<int>(info[0]).FromJust(), Nan::To<int>(info[1]).FromJust(),
        info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked(), info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
  } else {  // if (info.Length() == 5) {
    Matrix *other = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
    int x = Nan::To<int>(info[1]).FromJust();
    int y = info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    int w = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    int h = info[4]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    mat = new Matrix(other->mat, cv::Rect(x, y, w, h));
  }

  mat->Wrap(info.Holder());
  info.GetReturnValue().Set(info.Holder());
}

//Convenience factory method for creating a wrapped Matrix from a cv::Mat and tracking external memory correctly.
// Always tracks the referenced matrix as external memory.
Local<Object> Matrix::CreateWrappedFromMat(cv::Mat mat){
  Local < Object > result =
      Nan::NewInstance(Nan::GetFunction(Nan::New(Matrix::constructor)).ToLocalChecked()).ToLocalChecked();
  Matrix *m = Nan::ObjectWrap::Unwrap<Matrix>(result);
  m->setMat(mat);

  return result;
}

//Convenience factory method for creating a wrapped Matrix from a cv::Mat and tracking external memory correctly.
// Only tracks the referenced matrix as external memory if the refcount does not exceed the base refcount.
// Useful for creating a wrapper Matrix around a Mat that is also referenced by another wrapper Matrix
Local<Object> Matrix::CreateWrappedFromMatIfNotReferenced(cv::Mat mat, int baseRefCount){
  Local < Object > result =
      Nan::NewInstance(Nan::GetFunction(Nan::New(Matrix::constructor)).ToLocalChecked()).ToLocalChecked();
  Matrix *m = Nan::ObjectWrap::Unwrap<Matrix>(result);
  m->mat = mat;
  if (m->getWrappedRefCount() <= 2 + baseRefCount){ //one reference in m, one on the stack
    Nan::AdjustExternalMemory(m->mat.dataend - m->mat.datastart);
  }
  return result;
}

Matrix::Matrix() :
    node_opencv::Matrix() {
  mat = cv::Mat();
}

Matrix::Matrix(int rows, int cols) :
    node_opencv::Matrix() {
  mat = cv::Mat(rows, cols, CV_32FC3);
  Nan::AdjustExternalMemory(mat.dataend - mat.datastart);
}

Matrix::Matrix(int rows, int cols, int type) :
    node_opencv::Matrix() {
  mat = cv::Mat(rows, cols, type);
  Nan::AdjustExternalMemory(mat.dataend - mat.datastart);
}

Matrix::Matrix(Matrix *m) :
    node_opencv::Matrix() {
  mat = cv::Mat(m->mat);
}

Matrix::Matrix(cv::Mat m, cv::Rect roi) :
    node_opencv::Matrix() {
  mat = cv::Mat(m, roi);
}

Matrix::Matrix(int rows, int cols, int type, Local<Object> scalarObj) {
  mat = cv::Mat(rows, cols, type);
  Nan::AdjustExternalMemory(mat.dataend - mat.datastart);
  if (mat.channels() == 3) {
    mat.setTo(cv::Scalar(  
        Nan::To<double>( Nan::Get(scalarObj,0).ToLocalChecked() ).FromJust(),
        Nan::To<double>( Nan::Get(scalarObj,1).ToLocalChecked() ).FromJust(),
        Nan::To<double>( Nan::Get(scalarObj,2).ToLocalChecked() ).FromJust() 
    ));
  } else if (mat.channels() == 2) {
    mat.setTo(cv::Scalar(
        Nan::To<double>( Nan::Get(scalarObj,0).ToLocalChecked() ).FromJust(),
        Nan::To<double>( Nan::Get(scalarObj,1).ToLocalChecked() ).FromJust()
    ));
  } else if (mat.channels() == 1) {
    mat.setTo(cv::Scalar(
        Nan::To<double>( Nan::Get(scalarObj,0).ToLocalChecked() ).FromJust()
    ));
  } else {
    Nan::ThrowError("Only 1-3 channels are supported");
  }
}

Matrix::~Matrix(){
  if(getWrappedRefCount() == 1){ //if this holds the last reference to the Mat
    int size = mat.dataend - mat.datastart;
    Nan::AdjustExternalMemory(-1 * size);
  }
}

// Set the wrapped Mat with correct memory tracking
// For this to work correctly, there should be no external references held to our previous
// wrapped Mat, and no other Matrix objects should wrap a Mat pointing at the same
// memory as our new Mat.
void Matrix::setMat(cv::Mat m){
  int oldSize = 0;
  if(getWrappedRefCount() == 1){ //if this holds the last reference to the Mat
    oldSize = mat.dataend - mat.datastart;
  }
  mat = m;
  int newSize = mat.dataend - mat.datastart;
  Nan::AdjustExternalMemory(newSize - oldSize);
}

NAN_METHOD(Matrix::Empty) {
  SETUP_FUNCTION(Matrix)
  info.GetReturnValue().Set(Nan::New<Boolean>(self->mat.empty()));
}

double Matrix::DblGet(cv::Mat mat, int i, int j) {

  double val = 0;
  cv::Vec3b pix;
  unsigned int pint = 0;

  switch (mat.type()) {
    case CV_32FC3:
      pix = mat.at<cv::Vec3f>(i, j);
      pint |= (uchar) pix.val[2];
      pint |= ((uchar) pix.val[1]) << 8;
      pint |= ((uchar) pix.val[0]) << 16;
      val = (double) pint;
      break;
    case CV_64FC1:
      val = mat.at<double>(i, j);
      break;
    case CV_32FC1:
      val = mat.at<float>(i, j);
      break;
    default:
      val = mat.at<double>(i, j);
      break;
  }

  return val;
}

NAN_METHOD(Matrix::Pixel) {
  SETUP_FUNCTION(Matrix)

  int y = Nan::To<int>(info[0]).FromJust();
  int x = Nan::To<int>(info[1]).FromJust();

  // cv::Scalar scal = self->mat.at<uchar>(y, x);

  if (info.Length() == 3) {
    Local < Object > objColor = info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

    if (self->mat.channels() == 3) {
      self->mat.at<cv::Vec3b>(y, x)[0] =
          (uchar) Nan::To<uint32_t>( Nan::Get(objColor,0).ToLocalChecked() ).FromJust();
      self->mat.at<cv::Vec3b>(y, x)[1] =
          (uchar) Nan::To<uint32_t>( Nan::Get(objColor,1).ToLocalChecked() ).FromJust();
      self->mat.at<cv::Vec3b>(y, x)[2] =
          (uchar) Nan::To<uint32_t>( Nan::Get(objColor,2).ToLocalChecked() ).FromJust();
    } else if (self->mat.channels() == 1)
      self->mat.at<uchar>(y, x) = Nan::To<uint32_t>( Nan::Get(objColor,0).ToLocalChecked() ).FromJust();;

    info.GetReturnValue().Set(info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
  } else {
    if (self->mat.channels() == 3) {
      cv::Vec3b intensity = self->mat.at<cv::Vec3b>(y, x);

      v8::Local < v8::Array > arr = Nan::New<v8::Array>(3);
      Nan::Set(arr, 0, Nan::New<Number>(intensity[0]));
      Nan::Set(arr, 1, Nan::New<Number>(intensity[1]));
      Nan::Set(arr, 2, Nan::New<Number>(intensity[2]));
      info.GetReturnValue().Set(arr);
    } else if (self->mat.channels() == 1) {
      uchar intensity = self->mat.at<uchar>(y, x);
      info.GetReturnValue().Set(Nan::New<Number>(intensity));
    }
  }

  return;
  // double val = Matrix::DblGet(t, i, j);
  // info.GetReturnValue().Set(Nan::New<Number>(val));
}

NAN_METHOD(Matrix::Get) {
  SETUP_FUNCTION(Matrix)

  int i = Nan::To<int>(info[0]).FromJust();
  int j = Nan::To<int>(info[1]).FromJust();

  double val = Matrix::DblGet(self->mat, i, j);
  info.GetReturnValue().Set(Nan::New<Number>(val));
}

NAN_METHOD(Matrix::GetPixel) {
  SETUP_FUNCTION(Matrix)

  int y = Nan::To<int>(info[0]).FromJust();
  int x = Nan::To<int>(info[1]).FromJust();

  if (self->mat.channels() == 4) {
    v8::Local < v8::Array > arr = Nan::New<Array>(4);
    cv::Vec4b pixel = self->mat.at<cv::Vec4b>(y, x);
     Nan::Set(arr, 0, Nan::New<Number>((double) pixel.val[0]));
     Nan::Set(arr, 1, Nan::New<Number>((double) pixel.val[1]));
     Nan::Set(arr, 2, Nan::New<Number>((double) pixel.val[2]));
     Nan::Set(arr, 3, Nan::New<Number>((double) pixel.val[3]));
    info.GetReturnValue().Set(arr);
  } else if (self->mat.channels() == 3) {
    v8::Local < v8::Array > arr = Nan::New<Array>(3);
    cv::Vec3b pixel = self->mat.at<cv::Vec3b>(y, x);
     Nan::Set(arr, 0, Nan::New<Number>((double) pixel.val[0]));
     Nan::Set(arr, 1, Nan::New<Number>((double) pixel.val[1]));
     Nan::Set(arr, 2, Nan::New<Number>((double) pixel.val[2]));
    info.GetReturnValue().Set(arr);
  } else if(self->mat.channels() == 1) {
    int pixel = (int)self->mat.at<unsigned char>(y, x);
    info.GetReturnValue().Set(pixel);
  } else {
    Nan::ThrowTypeError("Only 4, 3 and 1 channel matrix are supported");
  }
}

NAN_METHOD(Matrix::Set) {
  SETUP_FUNCTION(Matrix)

  int i = Nan::To<int>(info[0]).FromJust();
  int j = Nan::To<int>(info[1]).FromJust();
  double val = info[2].As<Number>()->Value();
  int vint = 0;

  if (info.Length() == 4) {
    self->mat.at<cv::Vec3b>(i, j)[info[3].As<Number>()->Value()] = val;
  } else if (info.Length() == 3) {
    switch (self->mat.type()) {
      case CV_32FC3:
        vint = static_cast<unsigned int>(val + 0.5);
        self->mat.at<cv::Vec3f>(i, j)[0] = (uchar) (vint >> 16) & 0xff;
        self->mat.at<cv::Vec3f>(i, j)[1] = (uchar) (vint >> 8) & 0xff;
        self->mat.at<cv::Vec3f>(i, j)[2] = (uchar) (vint) & 0xff;
        // printf("!!!i %x, %x, %x", (vint >> 16) & 0xff, (vint >> 8) & 0xff, (vint) & 0xff);
        break;
      case CV_32FC1:
        self->mat.at<float>(i, j) = val;
        break;
      default:
        self->mat.at<double>(i, j) = val;
    }

  } else {
    Nan::ThrowTypeError("Invalid number of arguments");
  }

  return;
}

// @author tualo
// put node buffer directly into the image data
// img.put(new Buffer([0,100,0,100,100...]));
NAN_METHOD(Matrix::Put) {
  SETUP_FUNCTION(Matrix)

  if (!Buffer::HasInstance(info[0])) {
    Nan::ThrowTypeError("Not a buffer");
  }
  const char* buffer_data = Buffer::Data(info[0]);
  size_t buffer_length = Buffer::Length(info[0]);
  memcpy(self->mat.data, buffer_data, buffer_length);
  return;
}

// @author tualo
// getData getting node buffer of image data
NAN_METHOD(Matrix::GetData) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int size = self->mat.rows * self->mat.cols * self->mat.elemSize();
  Local<Object> buf = Nan::NewBuffer(size).ToLocalChecked();
  uchar* data = (uchar*) Buffer::Data(buf);
  // if there is padding after each row, clone first to get rid of it
  if (self->mat.dims == 2 && self->mat.step[0] != size_t(self->mat.size[1])) {
    cv::Mat copy = self->mat.clone();
    memcpy(data, copy.data, size);
  } else {
    memcpy(data, self->mat.data, size);
  }

  v8::Local<v8::Object> globalObj = Nan::GetCurrentContext()->Global();
  v8::Local<v8::Function> bufferConstructor = v8::Local<v8::Function>::Cast(Nan::Get(globalObj,Nan::New<String>("Buffer").ToLocalChecked()).ToLocalChecked());
  v8::Local<v8::Value> constructorArgs[3] = {buf, Nan::New<v8::Integer>((unsigned) size), Nan::New<v8::Integer>(0)};
  v8::Local<v8::Object> actualBuffer = Nan::NewInstance(bufferConstructor, 3, constructorArgs).ToLocalChecked();

  info.GetReturnValue().Set(actualBuffer);
}

NAN_METHOD(Matrix::Brightness) {
  Nan::HandleScope scope;
  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  if (info.Length() == 2) {
    cv::Mat image;

    if (self->mat.channels() == 3) {
      image = self->mat;
    } else if (self->mat.channels() == 1) {
      cv::Mat myimg = self->mat;
      cv::cvtColor(myimg, image, CV_GRAY2RGB);
    } else {
      Nan::ThrowError("those channels are not supported");
    }

    cv::Mat new_image = cv::Mat::zeros( image.size(), image.type() );
    double alpha = info[0].As<Number>()->Value();
    int beta = Nan::To<int>(info[1]).FromJust();

    // Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for (int y = 0; y < image.rows; y++ ) {
      for (int x = 0; x < image.cols; x++ ) {
        for (int c = 0; c < 3; c++ ) {
          new_image.at<cv::Vec3b>(y,x)[c] =
              cv::saturate_cast<uchar>(alpha*( image.at<cv::Vec3b>(y,x)[c] ) + beta);
        }
      }
    }

    if (self->mat.channels() == 3) {
      new_image.copyTo(self->mat);
    } else if (self->mat.channels() == 1) {
      cv::Mat gray;
      cv::cvtColor(new_image, gray, CV_BGR2GRAY);
      gray.copyTo(self->mat);
    }
  } else {
    if (info.Length() == 1) {
      int diff = Nan::To<int>(info[0]).FromJust();
      cv::Mat img = self->mat + diff;
      img.copyTo(self->mat);
    } else {
      info.GetReturnValue().Set(Nan::New("Insufficient or wrong arguments").ToLocalChecked());
    }
  }

  info.GetReturnValue().Set(Nan::Null());
}

int getNormType(int type) {
  if ((type != cv::NORM_MINMAX) && (type != cv::NORM_INF)
      && (type != cv::NORM_L1) && (type != cv::NORM_L2)
      && (type != cv::NORM_L2SQR) && (type != cv::NORM_HAMMING)
      && (type != cv::NORM_HAMMING2) && (type != cv::NORM_RELATIVE)
      && (type != cv::NORM_TYPE_MASK)) {
    Nan::ThrowTypeError("type value must be NORM_INF=1, NORM_L1=2, NORM_L2=4,"
        " NORM_L2SQR=5, NORM_HAMMING=6, NORM_HAMMING2=7, NORM_TYPE_MASK=7, "
        "NORM_RELATIVE=8, NORM_MINMAX=32 ");
  }
  return type;
}

// @author tualo
// normalize wrapper
NAN_METHOD(Matrix::Normalize) {
  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("min is required (argument 1)");
  }

  if (!info[1]->IsNumber()) {
    Nan::ThrowTypeError("max is required (argument 2)");
  }

  int type = cv::NORM_MINMAX;
  if (info[2]->IsNumber()) {
    type = getNormType(info[2]->Uint32Value(Nan::GetCurrentContext()).ToChecked());
  }
  int dtype = -1;
  if (info[3]->IsNumber()) {
    dtype = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
  }

  double min = info[0].As<Number>()->Value();
  double max = info[1].As<Number>()->Value();

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  cv::Mat norm;

  cv::Mat mask;
  if (info[4]->IsObject()) {
    Matrix *mmask = Nan::ObjectWrap::Unwrap<Matrix>(info[4]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    mask = mmask->mat;
  }

  cv::normalize(self->mat, norm, min, max, type, dtype, mask);

  norm.copyTo(self->mat);

  info.GetReturnValue().Set(Nan::Null());
}

/**
 * Calculates an absolute array norm, an absolute difference norm, or a relative
 * difference norm.
 *
 * Reference: http://docs.opencv.org/2.4/modules/core/doc/
 *            operations_on_arrays.html?highlight=normalize#norm
 */
NAN_METHOD(Matrix::Norm) {
  Matrix *src2 = NULL;
  int normType = cv::NORM_L2;
  cv::Mat mask;
  int infoCount = 0;

  Matrix *src1 = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  // If src2 is specified calculate absolute or relative difference norm
  if (!info[infoCount]->IsUndefined() && info[infoCount]->IsObject()) {
    src2 = Nan::ObjectWrap::Unwrap<Matrix>(info[infoCount]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    infoCount++;
  }

  // NORM_TYPE
  if (!info[infoCount]->IsUndefined() && info[infoCount]->IsInt32()) {
    normType = getNormType(info[infoCount]->Uint32Value(Nan::GetCurrentContext()).ToChecked());
    infoCount++;
  }

  // Mask
  if (!info[infoCount]->IsUndefined() && info[infoCount]->IsObject()) {
    Matrix *mmask = Nan::ObjectWrap::Unwrap<Matrix>(info[infoCount]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    mask = mmask->mat;
    infoCount++;
  }

  double res = 0;
  if (src2) {
    res = cv::norm(src1->mat, src2->mat, normType, mask);
  } else {
    res = cv::norm(src1->mat, normType, mask);
  }

  info.GetReturnValue().Set(Nan::New<Number>(res));
}

NAN_METHOD(Matrix::Size) {
  SETUP_FUNCTION(Matrix)

  v8::Local < v8::Array > arr = Nan::New<Array>(2);
   Nan::Set(arr, 0, Nan::New<Number>(self->mat.size().height));
   Nan::Set(arr, 1, Nan::New<Number>(self->mat.size().width));

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Matrix::Type) {
  SETUP_FUNCTION(Matrix)

  info.GetReturnValue().Set(Nan::New<Int32>(self->mat.type()));
}

NAN_METHOD(Matrix::Clone) {
  SETUP_FUNCTION(Matrix)

  Local<Object> im_h = Matrix::CreateWrappedFromMat(self->mat.clone());

  info.GetReturnValue().Set(im_h);
}

NAN_METHOD(Matrix::Crop) {
  SETUP_FUNCTION(Matrix)

  if ((info.Length() == 4) && (info[0]->IsNumber()) && (info[1]->IsNumber())
      && (info[2]->IsNumber()) && (info[3]->IsNumber())) {

    int x = Nan::To<int>(info[0]).FromJust();
    int y = Nan::To<int>(info[1]).FromJust();
    int width = info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    int height = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

    cv::Mat mat(self->mat, cv::Rect(x,y,width,height));

    Local < Object > im_h = Matrix::CreateWrappedFromMatIfNotReferenced(mat, 1);

    info.GetReturnValue().Set(im_h);
  } else {
    info.GetReturnValue().Set(Nan::New("Insufficient or wrong arguments").ToLocalChecked());
  }
}

NAN_METHOD(Matrix::Row) {
  SETUP_FUNCTION(Matrix)

  int width = self->mat.size().width;
  int y = Nan::To<int>(info[0]).FromJust();
  v8::Local < v8::Array > arr = Nan::New<Array>(width);

  for (int x = 0; x < width; x++) {
    double v = Matrix::DblGet(self->mat, y, x);
     Nan::Set(arr, x, Nan::New<Number>(v));
  }

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Matrix::PixelRow) {
  SETUP_FUNCTION(Matrix)

  int width = self->mat.size().width;
  int y = Nan::To<int>(info[0]).FromJust();
  v8::Local < v8::Array > arr;

  if (self->mat.channels() == 4) {
    arr = Nan::New<Array>(width * 4);
    for (int x = 0; x < width; x++) {
      cv::Vec4b pixel = self->mat.at<cv::Vec4b>(y, x);
      int offset = x * 4;
       Nan::Set(arr, offset, Nan::New<Number>((double) pixel.val[0]));
       Nan::Set(arr, offset + 1, Nan::New<Number>((double) pixel.val[1]));
       Nan::Set(arr, offset + 2, Nan::New<Number>((double) pixel.val[2]));
       Nan::Set(arr, offset + 3, Nan::New<Number>((double) pixel.val[3]));
    }
  } else if(self->mat.channels() == 3){
    arr = Nan::New<Array>(width * 3);
    for (int x = 0; x < width; x++) {
      cv::Vec3b pixel = self->mat.at<cv::Vec3b>(y, x);
      int offset = x * 3;
       Nan::Set(arr, offset, Nan::New<Number>((double) pixel.val[0]));
       Nan::Set(arr, offset + 1, Nan::New<Number>((double) pixel.val[1]));
       Nan::Set(arr, offset + 2, Nan::New<Number>((double) pixel.val[2]));
    }
  } else if(self->mat.channels() == 1){
    arr = Nan::New<Array>(width);
    for (int x = 0; x < width; x++) {
      int pixel = (int)self->mat.at<unsigned char>(y, x);
       Nan::Set(arr, x, Nan::New<Number>(pixel));
    }
  } else {
      Nan::ThrowTypeError("Only 4, 3 and 1 channel matrix are supported");
  }

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Matrix::Col) {
  SETUP_FUNCTION(Matrix)

  int height = self->mat.size().height;
  int x = Nan::To<int>(info[0]).FromJust();
  v8::Local < v8::Array > arr = Nan::New<Array>(height);

  for (int y = 0; y < height; y++) {
    double v = Matrix::DblGet(self->mat, y, x);
     Nan::Set(arr, y, Nan::New<Number>(v));
  }
  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Matrix::PixelCol) {
  SETUP_FUNCTION(Matrix)

  int height = self->mat.size().height;
  int x = Nan::To<int>(info[0]).FromJust();
  v8::Local < v8::Array > arr;

  if (self->mat.channels() == 4) {
    arr = Nan::New<Array>(height * 4);
    for (int y = 0; y < height; y++) {
      cv::Vec4b pixel = self->mat.at<cv::Vec4b>(y, x);
      int offset = y * 4;
       Nan::Set(arr, offset, Nan::New<Number>((double) pixel.val[0]));
       Nan::Set(arr, offset + 1, Nan::New<Number>((double) pixel.val[1]));
       Nan::Set(arr, offset + 2, Nan::New<Number>((double) pixel.val[2]));
       Nan::Set(arr, offset + 3, Nan::New<Number>((double) pixel.val[3]));
    }
  } else if (self->mat.channels() == 3) {
    arr = Nan::New<Array>(height * 3);
    for (int y = 0; y < height; y++) {
      cv::Vec3b pixel = self->mat.at<cv::Vec3b>(y, x);
      int offset = y * 3;
       Nan::Set(arr, offset, Nan::New<Number>((double) pixel.val[0]));
       Nan::Set(arr, offset + 1, Nan::New<Number>((double) pixel.val[1]));
       Nan::Set(arr, offset + 2, Nan::New<Number>((double) pixel.val[2]));
    }
  } else if(self->mat.channels() == 1) {
    arr = Nan::New<Array>(height);
    for (int y = 0; y < height; y++) {
      int pixel = (int)self->mat.at<unsigned char>(y, x);
       Nan::Set(arr, y, Nan::New<Number>(pixel));
    }
  } else {
    Nan::ThrowTypeError("Only 4, 3 and 1 channel matrix are supported");
  }

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Matrix::Width) {
  SETUP_FUNCTION(Matrix)

  info.GetReturnValue().Set(Nan::New<Number>(self->mat.size().width));
}

NAN_METHOD(Matrix::Height) {
  SETUP_FUNCTION(Matrix)

  info.GetReturnValue().Set(Nan::New<Number>(self->mat.size().height));
}

NAN_METHOD(Matrix::Channels) {
  SETUP_FUNCTION(Matrix)

  info.GetReturnValue().Set(Nan::New<Number>(self->mat.channels()));
}

NAN_METHOD(Matrix::ToBuffer) {
  SETUP_FUNCTION(Matrix)

  if ((info.Length() > 0) && (info[0]->IsFunction())) {
    return Matrix::ToBufferAsync(info);
  }

  // SergeMv changes
  // img.toBuffer({ext: ".png", pngCompression: 9}); // default png compression is 3
  // img.toBuffer({ext: ".jpg", jpegQuality: 80});
  // img.toBuffer(); // creates Jpeg with quality of 95 (Opencv default quality)
  // via the ext you can do other image formats too (like tiff), see
  // http://docs.opencv.org/modules/highgui/doc/reading_and_writing_images_and_video.html#imencode
  //---------------------------
  // Provide default value
  const char *ext = ".jpg";
  std::string optExt;
  std::vector<int> params;

  // See if the options argument is passed
  if ((info.Length() > 0) && (info[0]->IsObject())) {
    // Get this options argument
    v8::Local < v8::Object > options = v8::Local<v8::Object>::Cast(info[0]);
    // If the extension (image format) is provided
    if (options->Has( Nan::GetCurrentContext(), Nan::New<String>("ext").ToLocalChecked()).ToChecked() ) {
      v8::String::Utf8Value str(v8::Isolate::GetCurrent(),
          options->Get(Nan::GetCurrentContext(), Nan::New<String>("ext").ToLocalChecked()).ToLocalChecked()->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>()));
      optExt = *str;
      ext = (const char *) optExt.c_str();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("jpegQuality").ToLocalChecked()).ToChecked() ) {
      int compression =
          options->Get(Nan::GetCurrentContext(), Nan::New<String>("jpegQuality").ToLocalChecked()).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
      params.push_back(CV_IMWRITE_JPEG_QUALITY);
      params.push_back(compression);
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("pngCompression").ToLocalChecked()).ToChecked() ) {
      int compression =
          options->Get(Nan::GetCurrentContext(), Nan::New<String>("pngCompression").ToLocalChecked()).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
      params.push_back(CV_IMWRITE_PNG_COMPRESSION);
      params.push_back(compression);
    }
  }

  //---------------------------
  std::vector<uchar> vec(0);

  cv::imencode(ext, self->mat, vec, params);

  Local < Object > buf = Nan::NewBuffer(vec.size()).ToLocalChecked();
  uchar* data = (uchar*) Buffer::Data(buf);
  memcpy(data, &vec[0], vec.size());

  v8::Local < v8::Object > globalObj = Nan::GetCurrentContext()->Global();
  v8::Local < v8::Function > bufferConstructor = v8::Local < v8::Function
      > ::Cast(globalObj->Get(Nan::GetCurrentContext(), Nan::New<String>("Buffer").ToLocalChecked()).ToLocalChecked());
  v8::Local<v8::Value> constructorArgs[3] =
      {buf, Nan::New<v8::Integer>((unsigned)vec.size()), Nan::New<v8::Integer>(0)};
  v8::Local < v8::Object > actualBuffer = Nan::NewInstance(bufferConstructor, 3, constructorArgs).ToLocalChecked();

  info.GetReturnValue().Set(actualBuffer);
}

class AsyncToBufferWorker: public Nan::AsyncWorker {
public:
  AsyncToBufferWorker(Nan::Callback *callback, Matrix *matrix, std::string ext,
    std::vector<int> params) :
      Nan::AsyncWorker(callback),
      matrix(new Matrix(matrix)), // dulipcate matrix, adding ref, but not copying data
      ext(ext),
      params(params) {
  }

  ~AsyncToBufferWorker() {
      // mat is released, decrementing refcount
  }

  void Execute() {
    std::vector<uchar> vec(0);
    // std::vector<int> params(0);//CV_IMWRITE_JPEG_QUALITY 90
    cv::imencode(ext, matrix->mat, vec, this->params);
    res = vec;
  }

  void HandleOKCallback() {
    Nan::HandleScope scope;

    delete matrix;
    matrix = NULL;

    Local<Object> buf = Nan::NewBuffer(res.size()).ToLocalChecked();
    uchar* data = (uchar*) Buffer::Data(buf);
    memcpy(data, &res[0], res.size());

    v8::Local<v8::Object> globalObj = Nan::GetCurrentContext()->Global();
    v8::Local<v8::Function> bufferConstructor = v8::Local<v8::Function>::Cast(globalObj->Get(Nan::GetCurrentContext(), Nan::New<String>("Buffer").ToLocalChecked()).ToLocalChecked());
    v8::Local<v8::Value> constructorArgs[3] = {buf, Nan::New<v8::Integer>((unsigned)res.size()), Nan::New<v8::Integer>(0)};
    v8::Local<v8::Object> actualBuffer = Nan::NewInstance(bufferConstructor, 3, constructorArgs).ToLocalChecked();;

    Local<Value> argv[] = {
      Nan::Null(),
      actualBuffer
    };

    Nan::TryCatch try_catch;
    callback->Call(2, argv);
    if (try_catch.HasCaught()) {
      Nan::FatalException(try_catch);
    }

  }

private:
  Matrix *matrix;
  std::string ext;
  std::vector<int> params;
  std::vector<uchar> res;
};

NAN_METHOD(Matrix::ToBufferAsync) {
  SETUP_FUNCTION(Matrix)

  REQ_FUN_ARG(0, cb);

  std::string ext = std::string(".jpg");
  std::vector<int> params;

  // See if the options argument is passed
  if ((info.Length() > 1) && (info[1]->IsObject())) {
    // Get this options argument
    v8::Local < v8::Object > options = v8::Local<v8::Object>::Cast(info[1]);
    // If the extension (image format) is provided
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("ext").ToLocalChecked()).ToChecked() ) {
      v8::String::Utf8Value str(v8::Isolate::GetCurrent(),
          options->Get(Nan::GetCurrentContext(), Nan::New<String>("ext").ToLocalChecked()).ToLocalChecked()->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>()));
      std::string str2 = std::string(*str);
      ext = str2;
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("jpegQuality").ToLocalChecked()).ToChecked() ) {
      int compression =
          options->Get(Nan::GetCurrentContext(), Nan::New<String>("jpegQuality").ToLocalChecked()).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
      params.push_back(CV_IMWRITE_JPEG_QUALITY);
      params.push_back(compression);
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("pngCompression").ToLocalChecked()).ToChecked() ) {
      int compression =
          options->Get(Nan::GetCurrentContext(), Nan::New<String>("pngCompression").ToLocalChecked()).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
      params.push_back(CV_IMWRITE_PNG_COMPRESSION);
      params.push_back(compression);
    }
  }

  Nan::Callback *callback = new Nan::Callback(cb.As<Function>());
  Nan::AsyncQueueWorker(new AsyncToBufferWorker(callback, self, ext, params));

  return;
}

NAN_METHOD(Matrix::Ellipse) {
  SETUP_FUNCTION(Matrix)

  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
  cv::Scalar color(0, 0, 255);
  int thickness = 1;
  double angle = 0;
  double startAngle = 0;
  double endAngle = 360;
  int lineType = 8;
  int shift = 0;

  if (info[0]->IsObject()) {
    v8::Local < v8::Object > options = v8::Local<v8::Object>::Cast(info[0]);
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("center").ToLocalChecked()).ToChecked() ) {
      Local < Object > center =
          options->Get(Nan::GetCurrentContext(), Nan::New<String>("center").ToLocalChecked()).ToLocalChecked()->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      x = center->Get(Nan::GetCurrentContext(), Nan::New<String>("x").ToLocalChecked()).ToLocalChecked()->Uint32Value(Nan::GetCurrentContext()).ToChecked();
      y = center->Get(Nan::GetCurrentContext(), Nan::New<String>("y").ToLocalChecked()).ToLocalChecked()->Uint32Value(Nan::GetCurrentContext()).ToChecked();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("axes").ToLocalChecked()).ToChecked() ) {
      Local < Object > axes = options->Get(Nan::GetCurrentContext(), Nan::New<String>("axes").ToLocalChecked()).ToLocalChecked()->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      width = axes->Get(Nan::GetCurrentContext(), Nan::New<String>("width").ToLocalChecked()).ToLocalChecked()->Uint32Value(Nan::GetCurrentContext()).ToChecked();
      height = axes->Get(Nan::GetCurrentContext(), Nan::New<String>("height").ToLocalChecked()).ToLocalChecked()->Uint32Value(Nan::GetCurrentContext()).ToChecked();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("thickness").ToLocalChecked()).ToChecked() ) {
      thickness = options->Get(Nan::GetCurrentContext(), Nan::New<String>("thickness").ToLocalChecked()).ToLocalChecked()->Uint32Value(Nan::GetCurrentContext()).ToChecked();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("angle").ToLocalChecked()).ToChecked() ) {
      angle = options->Get(Nan::GetCurrentContext(), Nan::New<String>("angle").ToLocalChecked()).ToLocalChecked().As<Number>()->Value();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("startAngle").ToLocalChecked()).ToChecked() ) {
      startAngle = options->Get(Nan::GetCurrentContext(), Nan::New<String>("startAngle").ToLocalChecked()).ToLocalChecked().As<Number>()->Value();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("endAngle").ToLocalChecked()).ToChecked() ) {
      endAngle = options->Get(Nan::GetCurrentContext(), Nan::New<String>("endAngle").ToLocalChecked()).ToLocalChecked().As<Number>()->Value();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("lineType").ToLocalChecked()).ToChecked() ) {
      lineType = options->Get(Nan::GetCurrentContext(), Nan::New<String>("lineType").ToLocalChecked()).ToLocalChecked()->Uint32Value(Nan::GetCurrentContext()).ToChecked();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("shift").ToLocalChecked()).ToChecked() ) {
      shift = options->Get(Nan::GetCurrentContext(), Nan::New<String>("shift").ToLocalChecked()).ToLocalChecked()->Uint32Value(Nan::GetCurrentContext()).ToChecked();
    }
    if (options->Has( Nan::GetCurrentContext(),Nan::New<String>("color").ToLocalChecked()).ToChecked() ) {
      Local < Object > objColor =
          options->Get(Nan::GetCurrentContext(), Nan::New<String>("color").ToLocalChecked()).ToLocalChecked()->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      color = setColor(objColor);
    }
  } else {
    x = info[0]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
    y = info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
    width = info[2]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
    height = info[3]->Uint32Value(Nan::GetCurrentContext()).ToChecked();

    if (info[4]->IsArray()) {
      Local < Object > objColor = info[4]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      color = setColor(objColor);
    }

    if (info[5]->IntegerValue( Nan::GetCurrentContext() ).ToChecked())
      thickness = info[5]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
  }

  cv::ellipse(self->mat, cv::Point(x, y), cv::Size(width, height), angle,
      startAngle, endAngle, color, thickness, lineType, shift);
  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::Rectangle) {
  SETUP_FUNCTION(Matrix)

  if (info[0]->IsArray() && info[1]->IsArray()) {
    Local < Object > xy = Nan::To<v8::Object>(info[0]).ToLocalChecked();
    Local < Object > width_height = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

    cv::Scalar color(0, 0, 255);

    if (info[2]->IsArray()) {
      Local < Object > objColor = info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      color = setColor(objColor);
    }

    int x = xy->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    int y = xy->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

    int width = width_height->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    int height = width_height->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

    int thickness = 1;

    if (info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked())
      thickness = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

    cv::rectangle(self->mat, cv::Point(x, y), cv::Point(x + width, y + height),
        color, thickness);
  }

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::Line) {
  SETUP_FUNCTION(Matrix)

  if (info[0]->IsArray() && info[1]->IsArray()) {
    Local < Object > xy1 = Nan::To<v8::Object>(info[0]).ToLocalChecked();
    Local < Object > xy2 = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

    cv::Scalar color(0, 0, 255);

    if (info[2]->IsArray()) {
      Local < Object > objColor = info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      color = setColor(objColor);
    }

    int x1 = xy1->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    int y1 = xy1->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

    int x2 = xy2->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    int y2 = xy2->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

    int thickness = 1;

    if (info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked())
      thickness = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

    cv::line(self->mat, cv::Point(x1, y1), cv::Point(x2, y2), color, thickness);
  }

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::FillPoly) {
  SETUP_FUNCTION(Matrix)

  if (info[0]->IsArray()) {
    Local < Array > polyArray = Local < Array > ::Cast(Nan::To<v8::Object>(info[0]).ToLocalChecked());

    cv::Point **polygons = new cv::Point*[polyArray->Length()];
    int *polySizes = new int[polyArray->Length()];
    for (unsigned int i = 0; i < polyArray->Length(); i++) {
      Local<Array> singlePoly = Local<Array> ::Cast(polyArray->Get(Nan::GetCurrentContext(),i).ToLocalChecked()->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
      polygons[i] = new cv::Point[singlePoly->Length()];
      polySizes[i] = singlePoly->Length();

      for (unsigned int j = 0; j < singlePoly->Length(); j++) {
        Local<Array> point = Local<Array> ::Cast(singlePoly->Get(Nan::GetCurrentContext(),j).ToLocalChecked()->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
        polygons[i][j].x = point->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
        polygons[i][j].y = point->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
      }
    }

    cv::Scalar color(0, 0, 255);
    if (info[1]->IsArray()) {
      Local<Object> objColor = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
      color = setColor(objColor);
    }

    cv::fillPoly(self->mat, (const cv::Point **) polygons, polySizes,
        polyArray->Length(), color);
  }

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::Save) {
  SETUP_FUNCTION(Matrix)

  if (info.Length() > 1) {
    return SaveAsync(info);
  }

  if (!info[0]->IsString()) {
    Nan::ThrowTypeError("filename required");
  }

  Nan::Utf8String filename(info[0]);
  int res = cv::imwrite(*filename, self->mat);

  info.GetReturnValue().Set(Nan::New<Number>(res));
}

// All this is for async save, see here for nan example:
// https://github.com/rvagg/nan/blob/c579ae858ae3208d7e702e8400042ba9d48fa64b/examples/async_pi_estimate/async.cc
class AsyncSaveWorker: public Nan::AsyncWorker {
public:
  AsyncSaveWorker(Nan::Callback *callback, Matrix *matrix, char* filename) :
      Nan::AsyncWorker(callback),
      matrix(new Matrix(matrix)),
      filename(filename) {
  }

  ~AsyncSaveWorker() {
  }

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute() {
    res = cv::imwrite(this->filename, matrix->mat);
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback() {
    Nan::HandleScope scope;

    delete matrix;
    matrix = NULL;

    Local<Value> argv[] = {
      Nan::Null(),
      Nan::New<Number>(res)
    };

    Nan::TryCatch try_catch;
    callback->Call(2, argv);
    if (try_catch.HasCaught()) {
      Nan::FatalException(try_catch);
    }
  }

private:
  Matrix *matrix;
  std::string filename;
  int res;
};

NAN_METHOD(Matrix::SaveAsync) {
  SETUP_FUNCTION(Matrix)

  if (!info[0]->IsString()) {
    Nan::ThrowTypeError("filename required");
  }

  Nan::Utf8String filename(info[0]);

  REQ_FUN_ARG(1, cb);

  Nan::Callback *callback = new Nan::Callback(cb.As<Function>());
  Nan::AsyncQueueWorker(new AsyncSaveWorker(callback, self, *filename));

  return;
}

NAN_METHOD(Matrix::Zeros) {
  Nan::HandleScope scope;

  int h = info[0]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int w = info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int type = (info.Length() > 2) ? info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : CV_64FC1;

  cv::Mat mat = cv::Mat::zeros(h, w, type);
  Local<Object> im_h = Matrix::CreateWrappedFromMat(mat);
  info.GetReturnValue().Set(im_h);
}

NAN_METHOD(Matrix::Ones) {
  Nan::HandleScope scope;

  int h = info[0]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int w = info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int type = (info.Length() > 2) ? info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : CV_64FC1;

  cv::Mat mat = cv::Mat::ones(h, w, type);
  Local<Object> im_h = Matrix::CreateWrappedFromMat(mat);

  info.GetReturnValue().Set(im_h);
}

NAN_METHOD(Matrix::Eye) {
  Nan::HandleScope scope;

  int h = info[0]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int w = info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int type = (info.Length() > 2) ? info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : CV_64FC1;

  cv::Mat mat = cv::Mat::eye(h, w, type);
  Local<Object> im_h = Matrix::CreateWrappedFromMat(mat);

  info.GetReturnValue().Set(im_h);
}

NAN_METHOD(Matrix::ConvertGrayscale) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  if (self->mat.channels() != 3) {
    Nan::ThrowError("Image is no 3-channel");
  }

  int oldSize = self->mat.dataend - self->mat.datastart;
  cv::cvtColor(self->mat, self->mat, CV_BGR2GRAY);
  int newSize = self->mat.dataend - self->mat.datastart;
  Nan::AdjustExternalMemory(newSize - oldSize);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::ConvertHSVscale) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  if (self->mat.channels() != 3) {
    Nan::ThrowError("Image is no 3-channel");
  }

  cv::Mat hsv;

  cv::cvtColor(self->mat, hsv, CV_BGR2HSV);
  hsv.copyTo(self->mat);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::GaussianBlur) {
  Nan::HandleScope scope;
  cv::Size ksize;
  cv::Mat blurred;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  double sigmaX = 0;
  double sigmaY = 0;
  int borderType = cv::BORDER_DEFAULT;

  if (info.Length() < 1) {
    ksize = cv::Size(5, 5);
  }
  else {
    if (!info[0]->IsArray()) {
      Nan::ThrowTypeError("'ksize' argument must be a 2 double array");
    }
    Local<Object> array = Nan::To<v8::Object>(info[0]).ToLocalChecked();
    // TODO: Length check
    Local<Value> x = array->Get(Nan::GetCurrentContext(),0).ToLocalChecked();
    Local<Value> y = array->Get(Nan::GetCurrentContext(),1).ToLocalChecked();
    if (!x->IsNumber() || !y->IsNumber()) {
      Nan::ThrowTypeError("'ksize' argument must be a 2 double array");
    }
    ksize = cv::Size(x.As<Number>()->Value(), y.As<Number>()->Value());

    sigmaX = info.Length() < 2 ? 0 : info[1].As<Number>()->Value();
    sigmaY = info.Length() < 3 ? 0 : info[2].As<Number>()->Value();

    if (info.Length() == 4) {
      borderType = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    }
  }

  cv::GaussianBlur(self->mat, blurred, ksize, sigmaX, sigmaY, borderType);
  blurred.copyTo(self->mat);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::MedianBlur) {
  Nan::HandleScope scope;
  cv::Mat blurred;
  int ksize = 3;
  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  if (info[0]->IsNumber()) {
    ksize = Nan::To<int>(info[0]).FromJust();
    if ((ksize % 2) == 0) {
      Nan::ThrowTypeError("'ksize' argument must be a positive odd integer");
    }
  } else {
    Nan::ThrowTypeError("'ksize' argument must be a positive odd integer");
  }

  cv::medianBlur(self->mat, blurred, ksize);
  blurred.copyTo(self->mat);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::BilateralFilter) {
  Nan::HandleScope scope;
  cv::Mat filtered;
  int d = 15;
  double sigmaColor = 80;
  double sigmaSpace = 80;
  int borderType = cv::BORDER_DEFAULT;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  if (info.Length() != 0) {
    if (info.Length() < 3 || info.Length() > 4) {
      Nan::ThrowTypeError("BilateralFilter takes 0, 3, or 4 arguments");
    } else {
      d = Nan::To<int>(info[0]).FromJust();
      sigmaColor = info[1].As<Number>()->Value();
      sigmaSpace = info[2].As<Number>()->Value();
      if (info.Length() == 4) {
        borderType = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
      }
    }
  }

  cv::bilateralFilter(self->mat, filtered, d, sigmaColor, sigmaSpace, borderType);
  filtered.copyTo(self->mat);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::Sobel) {
  Nan::HandleScope scope;

  if (info.Length() < 3)
    Nan::ThrowError("Need more arguments: sobel(ddepth, xorder, yorder, ksize=3, scale=1.0, delta=0.0, borderType=CV_BORDER_DEFAULT)");

  int ddepth = Nan::To<int>(info[0]).FromJust();
  int xorder = Nan::To<int>(info[1]).FromJust();
  int yorder = info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

  int ksize = 3;
  if (info.Length() > 3) ksize = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
  double scale = 1;
  if (info.Length() > 4) scale = info[4].As<Number>()->Value();
  double delta = 0;
  if (info.Length() > 5) delta = info[5].As<Number>()->Value();
  int borderType = cv::BORDER_DEFAULT;
  if (info.Length() > 6) borderType = info[6]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  cv::Mat result;
  cv::Sobel(self->mat, result, ddepth, xorder, yorder, ksize, scale, delta, borderType);

  info.GetReturnValue().Set(CreateWrappedFromMat(result));
}

NAN_METHOD(Matrix::Copy) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  cv::Mat result;
  self->mat.copyTo(result);

  info.GetReturnValue().Set(CreateWrappedFromMat(result));
}

NAN_METHOD(Matrix::Flip) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  if ( info.Length() < 1 || !info[0]->IsInt32() ) {
    Nan::ThrowTypeError("Flip requires an integer flipCode argument "
        "(0 = X axis, positive = Y axis, negative = both axis)");
  }

  int flipCode = Nan::To<int>(info[0]).FromJust();

  cv::Mat result;
  cv::flip(self->mat, result, flipCode);

  info.GetReturnValue().Set(CreateWrappedFromMat(result));
}

NAN_METHOD(Matrix::ROI) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  if ( info.Length() != 4 ) {
    Nan::ThrowTypeError("ROI requires x,y,w,h arguments");
  }

  // Although it's an image to return, it is in fact a pointer to ROI of parent matrix

  int x = Nan::To<int>(info[0]).FromJust();
  int y = Nan::To<int>(info[1]).FromJust();
  int w = info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
  int h = info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

  cv::Mat roi(self->mat, cv::Rect(x,y,w,h));
  // Although it's an image to return, it is in fact a pointer to ROI of parent matrix
  Local<Object> img_to_return = Matrix::CreateWrappedFromMatIfNotReferenced(roi, 1);

  info.GetReturnValue().Set(img_to_return);
}

NAN_METHOD(Matrix::Ptr) {
  Nan::HandleScope scope;
  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int line = info[0]->Uint32Value(Nan::GetCurrentContext()).ToChecked();

  char* data = self->mat.ptr<char>(line);
  // uchar* data = self->mat.data;

  // char *mydata = "Random raw data\0";
  Local<Object> return_buffer = Nan::NewBuffer((char*)data, self->mat.step).ToLocalChecked();
  info.GetReturnValue().Set( return_buffer );
//  return;
}

NAN_METHOD(Matrix::AbsDiff) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Matrix *src1 = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  Matrix *src2 = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
  cv::absdiff(src1->mat, src2->mat, self->mat);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::Dct) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int cols = self->mat.cols;
  int rows = self->mat.rows;

  cv::Mat result(cols, rows, CV_32F);

  cv::dct(self->mat, result);

  info.GetReturnValue().Set(CreateWrappedFromMat(result));
}

NAN_METHOD(Matrix::Idct) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int cols = self->mat.cols;
  int rows = self->mat.rows;

  cv::Mat result(cols, rows, CV_32F);

  cv::idct(self->mat, result);

  info.GetReturnValue().Set(CreateWrappedFromMat(result));
}

NAN_METHOD(Matrix::AddWeighted) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Matrix *src1 = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  Matrix *src2 = Nan::ObjectWrap::Unwrap<Matrix>(info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());

  float alpha = info[1].As<Number>()->Value();
  float beta = info[3].As<Number>()->Value();
  int gamma = 0;

  try {
    cv::addWeighted(src1->mat, alpha, src2->mat, beta, gamma, self->mat);
  } catch(cv::Exception& e ) {
    const char* err_msg = e.what();
    Nan::ThrowError(err_msg);
  }

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::Add) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int cols = self->mat.cols;
  int rows = self->mat.rows;

  Matrix *src1 = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  try {
    cv::Mat outputmat = cv::Mat(cols, rows, self->mat.type());
    cv::add(self->mat, src1->mat, outputmat);
    Local<Object> out = CreateWrappedFromMat(outputmat);
    info.GetReturnValue().Set(out);
  } catch(cv::Exception& e ) {
    const char* err_msg = e.what();
    Nan::ThrowError(err_msg);
  }
}

NAN_METHOD(Matrix::BitwiseXor) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Matrix *src1 = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  Matrix *src2 = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());

  if (info.Length() == 3) {
    Matrix *mask = Nan::ObjectWrap::Unwrap<Matrix>(info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    cv::bitwise_xor(src1->mat, src2->mat, self->mat, mask->mat);
  } else {
    cv::bitwise_xor(src1->mat, src2->mat, self->mat);
  }

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::BitwiseNot) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Matrix *dst = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  if (info.Length() == 2) {
    Matrix *mask = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    cv::bitwise_not(self->mat, dst->mat, mask->mat);
  } else {
    cv::bitwise_not(self->mat, dst->mat);
  }

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::BitwiseAnd) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Matrix *src1 = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  Matrix *src2 = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
  if (info.Length() == 3) {
    Matrix *mask = Nan::ObjectWrap::Unwrap<Matrix>(info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    cv::bitwise_and(src1->mat, src2->mat, self->mat, mask->mat);
  } else {
    cv::bitwise_and(src1->mat, src2->mat, self->mat);
  }

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::CountNonZero) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  double count = (double)cv::countNonZero(self->mat);

  info.GetReturnValue().Set(Nan::New<Number>(count));
}

/*
NAN_METHOD(Matrix::Split) {
  Nan::HandleScope scope;

  //Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  info.GetReturnValue().Set(Nan::Null());
} */

NAN_METHOD(Matrix::Moments) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  cv::Moments mo = moments( self->mat, false );

  Local<Object> res = Nan::New<Object>();

  res->Set(Nan::GetCurrentContext(),Nan::New("m00").ToLocalChecked(), Nan::New<Number>(mo.m00));
  res->Set(Nan::GetCurrentContext(),Nan::New("m10").ToLocalChecked(), Nan::New<Number>(mo.m10));
  res->Set(Nan::GetCurrentContext(),Nan::New("m01").ToLocalChecked(), Nan::New<Number>(mo.m01));
  res->Set(Nan::GetCurrentContext(),Nan::New("m20").ToLocalChecked(), Nan::New<Number>(mo.m20));
  res->Set(Nan::GetCurrentContext(),Nan::New("m11").ToLocalChecked(), Nan::New<Number>(mo.m11));
  res->Set(Nan::GetCurrentContext(),Nan::New("m02").ToLocalChecked(), Nan::New<Number>(mo.m02));
  res->Set(Nan::GetCurrentContext(),Nan::New("m30").ToLocalChecked(), Nan::New<Number>(mo.m30));
  res->Set(Nan::GetCurrentContext(),Nan::New("m21").ToLocalChecked(), Nan::New<Number>(mo.m21));
  res->Set(Nan::GetCurrentContext(),Nan::New("m12").ToLocalChecked(), Nan::New<Number>(mo.m12));
  res->Set(Nan::GetCurrentContext(),Nan::New("m03").ToLocalChecked(), Nan::New<Number>(mo.m03));

  res->Set(Nan::GetCurrentContext(),Nan::New("mu20").ToLocalChecked(), Nan::New<Number>(mo.mu20));
  res->Set(Nan::GetCurrentContext(),Nan::New("mu11").ToLocalChecked(), Nan::New<Number>(mo.mu11));
  res->Set(Nan::GetCurrentContext(),Nan::New("mu02").ToLocalChecked(), Nan::New<Number>(mo.mu02));
  res->Set(Nan::GetCurrentContext(),Nan::New("mu30").ToLocalChecked(), Nan::New<Number>(mo.mu30));
  res->Set(Nan::GetCurrentContext(),Nan::New("mu21").ToLocalChecked(), Nan::New<Number>(mo.mu21));
  res->Set(Nan::GetCurrentContext(),Nan::New("mu12").ToLocalChecked(), Nan::New<Number>(mo.mu12));
  res->Set(Nan::GetCurrentContext(),Nan::New("mu03").ToLocalChecked(), Nan::New<Number>(mo.mu03));

  res->Set(Nan::GetCurrentContext(),Nan::New("nu20").ToLocalChecked(), Nan::New<Number>(mo.nu20));
  res->Set(Nan::GetCurrentContext(),Nan::New("nu11").ToLocalChecked(), Nan::New<Number>(mo.nu11));
  res->Set(Nan::GetCurrentContext(),Nan::New("nu02").ToLocalChecked(), Nan::New<Number>(mo.nu02));
  res->Set(Nan::GetCurrentContext(),Nan::New("nu30").ToLocalChecked(), Nan::New<Number>(mo.nu30));
  res->Set(Nan::GetCurrentContext(),Nan::New("nu21").ToLocalChecked(), Nan::New<Number>(mo.nu21));
  res->Set(Nan::GetCurrentContext(),Nan::New("nu12").ToLocalChecked(), Nan::New<Number>(mo.nu12));
  res->Set(Nan::GetCurrentContext(),Nan::New("nu03").ToLocalChecked(), Nan::New<Number>(mo.nu03));

  info.GetReturnValue().Set(res);
}

NAN_METHOD(Matrix::Canny) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int lowThresh = info[0].As<Number>()->Value();
  int highThresh = info[1].As<Number>()->Value();

  cv::Mat newMat;
  cv::Canny(self->mat, newMat, lowThresh, highThresh);
  newMat.copyTo(self->mat);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::Dilate) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int niters = info[0].As<Number>()->Value();

  cv::Mat kernel = cv::Mat();
  if (info.Length() == 2) {
    Matrix *kernelMatrix = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    kernel = kernelMatrix->mat;
  }

  cv::dilate(self->mat, self->mat, kernel, cv::Point(-1, -1), niters);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::Erode) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int niters = info[0].As<Number>()->Value();

  cv::Mat kernel = cv::Mat();
  if (info.Length() == 2) {
    Matrix *kernelMatrix = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
    kernel = kernelMatrix->mat;
  }
  cv::erode(self->mat, self->mat, kernel, cv::Point(-1, -1), niters);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::FindContours) {
  Nan::HandleScope scope;

  int mode = CV_RETR_LIST;
  int chain = CV_CHAIN_APPROX_SIMPLE;

  if (info.Length() > 0) {
    if (info[0]->IsNumber()) mode = Nan::To<int>(info[0]).FromJust();
  }

  if (info.Length() > 1) {
    if (info[1]->IsNumber()) chain = Nan::To<int>(info[1]).FromJust();
  }

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Local<Object> conts_to_return = Nan::NewInstance(Nan::GetFunction(Nan::New(Contour::constructor)).ToLocalChecked()).ToLocalChecked();
  Contour *contours = Nan::ObjectWrap::Unwrap<Contour>(conts_to_return);

  cv::findContours(self->mat, contours->contours, contours->hierarchy, mode, chain);

  info.GetReturnValue().Set(conts_to_return);

}

NAN_METHOD(Matrix::DrawContour) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Contour *cont = Nan::ObjectWrap::Unwrap<Contour>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  int pos = info[1].As<Number>()->Value();
  cv::Scalar color(0, 0, 255);

  if (info[2]->IsArray()) {
    Local<Object> objColor = info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    color = setColor(objColor);
  }

  int thickness = info.Length() < 4 ? 1 : info[3].As<Number>()->Value();
  int lineType = info.Length() < 5 ? 8 : info[4].As<Number>()->Value();
  int maxLevel = info.Length() < 6 ? 0 : info[5].As<Number>()->Value();

  cv::Point offset;
  if (info.Length() == 6) {
    Local<Array> _offset = Local<Array>::Cast(info[5]);
    offset = cv::Point(
            Nan::To<int>(Nan::Get(_offset, 0).ToLocalChecked()).FromJust(),
            Nan::To<int>(Nan::Get(_offset, 1).ToLocalChecked()).FromJust()
    );
  }

  cv::drawContours(self->mat, cont->contours, pos, color, thickness, lineType, cont->hierarchy, maxLevel, offset);

  return;
}

NAN_METHOD(Matrix::DrawAllContours) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Contour *cont = Nan::ObjectWrap::Unwrap<Contour>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  cv::Scalar color(0, 0, 255);

  if (info[1]->IsArray()) {
    Local<Object> objColor = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    color = setColor(objColor);
  }

  int thickness = info.Length() < 3 ? 1 : info[2].As<Number>()->Value();
  cv::drawContours(self->mat, cont->contours, -1, color, thickness);

  return;
}

NAN_METHOD(Matrix::GoodFeaturesToTrack) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int maxCorners = info.Length() >= 1 ? Nan::To<int>(info[0]).FromJust() : 500;
  double qualityLevel = info.Length() >= 2 ? (double) info[1].As<Number>()->Value() : 0.01;
  double minDistance = info.Length() >= 3 ? (double) info[2].As<Number>()->Value() : 10;
  int blockSize = info.Length() >= 4 ? info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : 3;
  bool useHarrisDetector = info.Length() >= 5 ? info[4]->BooleanValue( v8::Isolate::GetCurrent() ) : false;
  double k = info.Length() >= 6 ? (double) info[5].As<Number>()->Value() : 0.04;

  std::vector<cv::Point2f> corners;
  cv::Mat gray;

   if (self->mat.channels() == 1) {
     gray = self->mat;
   } else {
     cvtColor(self->mat, gray, CV_BGR2GRAY);
     equalizeHist(gray, gray);
   }

  cv::goodFeaturesToTrack(gray, corners, maxCorners, qualityLevel, minDistance, cv::noArray(), blockSize, useHarrisDetector, k);
  v8::Local<v8::Array> arr = Nan::New<Array>(corners.size());

  for (unsigned int i=0; i<corners.size(); i++) {
    v8::Local<v8::Array> pt = Nan::New<Array>(2);
    pt->Set(Nan::GetCurrentContext(),0, Nan::New<Number>((double) corners[i].x));
    pt->Set(Nan::GetCurrentContext(),1, Nan::New<Number>((double) corners[i].y));
     Nan::Set(arr, i, pt);
  }

  info.GetReturnValue().Set(arr);
}

#ifdef HAVE_OPENCV_VIDEO
NAN_METHOD(Matrix::CalcOpticalFlowPyrLK) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Matrix *newMatrix = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  Local<Array> points = Local<Array>::Cast(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());
  std::vector<cv::Point2f> old_points;

  for (unsigned int i=0; i<points->Length(); i++) {
    Local<Object> pt = points->Get(Nan::GetCurrentContext(),i).ToLocalChecked()->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    old_points.push_back(cv::Point2f(pt->Get(Nan::GetCurrentContext(),0).ToLocalChecked().As<Number>()->Value(), pt->Get(Nan::GetCurrentContext(),1).ToLocalChecked().As<Number>()->Value()));
  }

  cv::Size winSize;
  if (info.Length() >= 3 && info[2]->IsArray()) {
    Local<Object> winSizeObj = info[2]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    winSize = cv::Size(winSizeObj->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked(), winSizeObj->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked());
  } else {
    winSize = cv::Size(21, 21);
  }

  int maxLevel = info.Length() >= 4 ? info[3]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : 3;

  cv::TermCriteria criteria;
  if (info.Length() >= 5 && info[4]->IsArray()) {
    Local<Object> criteriaObj = info[4]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    criteria = cv::TermCriteria(criteriaObj->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked(), criteriaObj->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked(), (double) criteriaObj->Get(Nan::GetCurrentContext(),2).ToLocalChecked().As<Number>()->Value());
  } else {
    criteria = cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 30, 0.01);
  }

  int flags = info.Length() >= 6 ? info[5]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : 0;
  double minEigThreshold = info.Length() >= 7 ? info[6].As<Number>()->Value() : 1e-4;

  cv::Mat old_gray;
  cv::cvtColor(self->mat, old_gray, CV_BGR2GRAY);

  cv::Mat new_gray;
  cv::cvtColor(newMatrix->mat, new_gray, CV_BGR2GRAY);

  std::vector<cv::Point2f> new_points;
  std::vector<uchar> status;
  std::vector<float> err;

  cv::calcOpticalFlowPyrLK(old_gray, new_gray, old_points, new_points, status, err, winSize, maxLevel, criteria, flags, minEigThreshold);

  v8::Local<v8::Array> old_arr = Nan::New<Array>(old_points.size());
  v8::Local<v8::Array> new_arr = Nan::New<Array>(new_points.size());
  v8::Local<v8::Array> found = Nan::New<Array>(status.size());

  for (unsigned int i=0; i<old_points.size(); i++) {
    v8::Local<v8::Array> pt = Nan::New<Array>(2);
    pt->Set(Nan::GetCurrentContext(),0, Nan::New<Number>((double) old_points[i].x));
    pt->Set(Nan::GetCurrentContext(),1, Nan::New<Number>((double) old_points[i].y));
    new_arr->Set(Nan::GetCurrentContext(), i, pt);
  }

  for (unsigned int i=0; i<new_points.size(); i++) {
    v8::Local<v8::Array> pt = Nan::New<Array>(2);
    pt->Set(Nan::GetCurrentContext(),0, Nan::New<Number>((double) new_points[i].x));
    pt->Set(Nan::GetCurrentContext(),1, Nan::New<Number>((double) new_points[i].y));
    new_arr->Set(Nan::GetCurrentContext(), i, pt);
  }

  for (unsigned int i=0; i<status.size(); i++) {
    v8::Local<v8::Integer> pt = Nan::New<Integer>((int)status[i]);
    found->Set(Nan::GetCurrentContext(),i, pt);
  }

  Local<Object> data = Nan::New<Object>();
  data->Set(Nan::GetCurrentContext(),Nan::New<String>("old_points").ToLocalChecked(), old_arr);
  data->Set(Nan::GetCurrentContext(),Nan::New<String>("new_points").ToLocalChecked(), new_arr);
  data->Set(Nan::GetCurrentContext(),Nan::New<String>("found").ToLocalChecked(), found);

  info.GetReturnValue().Set(data);
}
#endif

NAN_METHOD(Matrix::HoughLinesP) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  double rho = info.Length() < 1 ? 1 : info[0].As<Number>()->Value();
  double theta = info.Length() < 2 ? CV_PI/180 : info[1].As<Number>()->Value();
  int threshold = info.Length() < 3 ? 80 : info[2]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  double minLineLength = info.Length() < 4 ? 30 : info[3].As<Number>()->Value();
  double maxLineGap = info.Length() < 5 ? 10 : info[4].As<Number>()->Value();
  std::vector<cv::Vec4i> lines;

  cv::Mat gray;

  equalizeHist(self->mat, gray);
  // cv::Canny(gray, gray, 50, 200, 3);
  cv::HoughLinesP(gray, lines, rho, theta, threshold, minLineLength, maxLineGap);

  v8::Local<v8::Array> arr = Nan::New<Array>(lines.size());

  for (unsigned int i=0; i<lines.size(); i++) {
    v8::Local<v8::Array> pt = Nan::New<Array>(4);
    pt->Set(Nan::GetCurrentContext(),0, Nan::New<Number>((double) lines[i][0]));
    pt->Set(Nan::GetCurrentContext(),1, Nan::New<Number>((double) lines[i][1]));
    pt->Set(Nan::GetCurrentContext(),2, Nan::New<Number>((double) lines[i][2]));
    pt->Set(Nan::GetCurrentContext(),3, Nan::New<Number>((double) lines[i][3]));
     Nan::Set(arr, i, pt);
  }

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Matrix::HoughCircles) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  double dp = info.Length() < 1 ? 1 : info[0].As<Number>()->Value();
  double minDist = info.Length() < 2 ? 1 : info[1].As<Number>()->Value();
  double higherThreshold = info.Length() < 3 ? 100 : info[2].As<Number>()->Value();
  double accumulatorThreshold = info.Length() < 4 ? 100 : info[3].As<Number>()->Value();
  int minRadius = info.Length() < 5 ? 0 : info[4]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int maxRadius = info.Length() < 6 ? 0 : info[5]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  std::vector<cv::Vec3f> circles;

  cv::Mat gray;

  equalizeHist(self->mat, gray);

  cv::HoughCircles(gray, circles, CV_HOUGH_GRADIENT, dp, minDist,
      higherThreshold, accumulatorThreshold, minRadius, maxRadius);

  v8::Local<v8::Array> arr = Nan::New<Array>(circles.size());

  for (unsigned int i=0; i < circles.size(); i++) {
    v8::Local<v8::Array> pt = Nan::New<Array>(3);
    pt->Set(Nan::GetCurrentContext(),0, Nan::New<Number>((double) circles[i][0]));  // center x
    pt->Set(Nan::GetCurrentContext(),1, Nan::New<Number>((double) circles[i][1]));// center y
    pt->Set(Nan::GetCurrentContext(),2, Nan::New<Number>((double) circles[i][2]));// radius
     Nan::Set(arr, i, pt);
  }

  info.GetReturnValue().Set(arr);
}

cv::Scalar setColor(Local<Object> objColor) {
  int64_t channels[4] = { 0, 0, 0, 0 };

  // We'll accomodate a channel count up to 4 and fall back to the old
  // "assume it's always 3" in the default case
  if (!objColor->HasRealIndexedProperty( Nan::GetCurrentContext() , 1).ToChecked()) {
    channels[0] = objColor->Get(Nan::GetCurrentContext(), 0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
  } else if (!objColor->HasRealIndexedProperty( Nan::GetCurrentContext() , 2).ToChecked()) {
    channels[0] = objColor->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    channels[1] = objColor->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
  } else if (!objColor->HasRealIndexedProperty( Nan::GetCurrentContext() , 4).ToChecked()) {
    channels[0] = objColor->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    channels[1] = objColor->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    channels[2] = objColor->Get(Nan::GetCurrentContext(),2).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    channels[3] = objColor->Get(Nan::GetCurrentContext(),3).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
  } else {
    channels[0] = objColor->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    channels[1] = objColor->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    channels[2] = objColor->Get(Nan::GetCurrentContext(),2).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
  }

  return cv::Scalar(channels[0], channels[1], channels[2], channels[3]);
}

cv::Point setPoint(Local<Object> objPoint) {
  return cv::Point(objPoint->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked(),
      objPoint->Get(Nan::GetCurrentContext(),1).ToLocalChecked()->IntegerValue( Nan::GetCurrentContext() ).ToChecked());
}

cv::Rect* setRect(Local<Object> objRect, cv::Rect &result) {
  if (!objRect->IsArray() || !objRect->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IsArray()
      || !objRect->Get(Nan::GetCurrentContext(),0).ToLocalChecked()->IsArray()) {
    printf("error");
    return 0;
  };

  Local < Object > point =  Nan::To<Object>( Nan::Get(objRect,0).ToLocalChecked() ).ToLocalChecked();;
  Local < Object > size =  Nan::To<Object>( Nan::Get(objRect,1).ToLocalChecked() ).ToLocalChecked();

  result.x = Nan::To<int32_t>( Nan::Get(point,0).ToLocalChecked() ).FromJust();
  result.y = Nan::To<int32_t>( Nan::Get(point,1).ToLocalChecked() ).FromJust();
  result.width = Nan::To<int32_t>( Nan::Get(size,0).ToLocalChecked() ).FromJust();
  result.height = Nan::To<int32_t>( Nan::Get(size,1).ToLocalChecked() ).FromJust();

  return &result;
}


class ResizeASyncWorker: public Nan::AsyncWorker {
public:
  ResizeASyncWorker(Nan::Callback *callback, Matrix *image, cv::Size size, double fx, double fy, int interpolation) :
      Nan::AsyncWorker(callback),
      image(new Matrix(image)),
      dest(cv::Mat()),
      size(size),
      fx(fx),
      fy(fy),
      interpolation(interpolation),
      success(0) {
  }
    
  ~ResizeASyncWorker() {
    // Any cleanup we needed to do could be done here.
    // Clean up of the input image Matrix and the destination cv::Mat
    // should be handled automatically by destructors.
  }

  void Execute() {
    try {
        cv::resize(image->mat, dest, size, fx, fy, interpolation);
        success = 1;
    } catch(...){
        success = 0;
    }
  }

  void HandleOKCallback() {
    Nan::HandleScope scope;

    delete image;
    image = NULL;
    
    if (success){
        try{
            Local<Object> im_to_return = Matrix::CreateWrappedFromMat(dest);
            dest.release(); //release our refcount before handing it back to the callback

            Local<Value> argv[] = {
              Nan::Null(), // err
              im_to_return //result
            };

            Nan::TryCatch try_catch;
            callback->Call(2, argv);
            if (try_catch.HasCaught()) {
              Nan::FatalException(try_catch);
            }
        } catch (...){
            Local<Value> argv[] = {
              Nan::New("C++ exception wrapping response").ToLocalChecked(), // err
              Nan::Null() // result
            };

            Nan::TryCatch try_catch;
            callback->Call(2, argv);
            if (try_catch.HasCaught()) {
              Nan::FatalException(try_catch);
            }
        }
    } else {
        Local<Value> argv[] = {
          Nan::New("C++ exception").ToLocalChecked(), // err
          Nan::Null() //result
        };

        Nan::TryCatch try_catch;
        callback->Call(2, argv);
        if (try_catch.HasCaught()) {
          Nan::FatalException(try_catch);
        }
    }
  }

private:
  Matrix *image;
  cv::Mat dest;
  cv::Size size;
  double fx;
  double fy;
  int interpolation;
  int success;

};


NAN_METHOD(Matrix::Resize) {
  SETUP_FUNCTION(Matrix)

  if (info.Length() < 2) {
    return Nan::ThrowError("Matrix.resize requires at least 2 argument2");
  }

  //im.resize( width, height );
  //im.resize( width, height, fx, fy );
  //im.resize( width, height, interpolation );
  //im.resize( width, height, fx, fy, interpolation );
  // if fn is added on the end, makes it Async
  
  int numargs = info.Length();
  int isAsync = 0;
  
  if (info[numargs-1]->IsFunction()){
      isAsync = 1;
  }

  if (info.Length() < 2+isAsync) {
    return Nan::ThrowError("Matrix.resize requires at least x and y size argument2");
  }

  int x = info[0]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int y = info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();

  cv::Size size(x, y);
  
  if (size.area() == 0) {
    return Nan::ThrowError("Area of size must be > 0");
  }

  double fx = 0;
  double fy = 0;
  int interpolation = cv::INTER_LINEAR;

  // if 4 or more args, then expect fx, fy next
  if (numargs >= 4+isAsync) {
    DOUBLE_FROM_ARGS(fx, 2)
    DOUBLE_FROM_ARGS(fy, 3)
    if (numargs == 5+isAsync) {
      INT_FROM_ARGS(interpolation, 5)
    }
  } else {
    // if 3 args after possible function, expect interpolation
    if (numargs == 3+isAsync) {
      INT_FROM_ARGS(interpolation, 3)
    }
  }
  
  // if async
  if (isAsync){
    REQ_FUN_ARG(numargs-1, cb);
    Nan::Callback *callback = new Nan::Callback(cb.As<Function>());
    Nan::AsyncQueueWorker(new ResizeASyncWorker(callback, self, size, fx, fy, interpolation));
    info.GetReturnValue().Set(Nan::Null());
  } else {
    try{
        Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
        cv::Mat res = cv::Mat(x, y, CV_32FC3);
        cv::resize(self->mat, res, cv::Size(x, y), 0, 0, interpolation);
        self->setMat(res);
    } catch (...){
        return Nan::ThrowError("c++ Exception processing resize");
    }
  }
}

NAN_METHOD(Matrix::Rotate) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  cv::Mat rotMatrix(2, 3, CV_32FC1);
  cv::Mat res;

  float angle = Nan::To<double>(info[0]).FromJust();

  // Modification by SergeMv
  //-------------
  // If you provide only the angle argument and the angle is multiple of 90, then
  // we do a fast thing
  bool rightOrStraight = (ceil(angle) == angle) && (!((int)angle % 90))
      && (info.Length() == 1);
  if (rightOrStraight) {
    int angle2 = ((int)angle) % 360;
    if (!angle2) {return;}
    if (angle2 < 0) {angle2 += 360;}
    // See if we do right angle rotation, we transpose the matrix:
    if (angle2 % 180) {
      cv::transpose(self->mat, res);
      self->setMat(res);
    }
    // Now flip the image
    int mode = -1;// flip around both axes
    // If counterclockwise, flip around the x-axis
    if (angle2 == 90) {mode = 0;}
    // If clockwise, flip around the y-axis
    if (angle2 == 270) {mode = 1;}
    cv::flip(self->mat, self->mat, mode);
    return;
  }

  //-------------
  int x = info[1]->IsUndefined() ? round(self->mat.size().width / 2) :
      info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int y = info[1]->IsUndefined() ? round(self->mat.size().height / 2) :
      info[2]->Uint32Value(Nan::GetCurrentContext()).ToChecked();

  cv::Point center = cv::Point(x,y);
  rotMatrix = getRotationMatrix2D(center, angle, 1.0);

  cv::warpAffine(self->mat, res, rotMatrix, self->mat.size());
  self->setMat(res);

  return;
}

NAN_METHOD(Matrix::GetRotationMatrix2D) {
  Nan::HandleScope scope;
  if (info.Length() < 3) {
    JSTHROW("Invalid number of arguments");
  }

  float angle = Nan::To<double>(info[0]).FromJust();
  int x = Nan::To<uint32_t>(info[1]).FromJust();
  int y = Nan::To<uint32_t>(info[2]).FromJust();
  double scale = Nan::To<double>(info[3]).FromMaybe(1.0);

  cv::Point center = cv::Point(x,y);
  Local<Object> img_to_return = Matrix::CreateWrappedFromMat(getRotationMatrix2D(center, angle, scale));

  info.GetReturnValue().Set(img_to_return);
}

NAN_METHOD(Matrix::WarpAffine) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  cv::Mat res;

  Matrix *rotMatrix = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  // Resize the image if size is specified
  int dstRows = info[1]->IsUndefined() ? self->mat.rows : info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int dstCols = info[2]->IsUndefined() ? self->mat.cols : info[2]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  cv::Size resSize = cv::Size(dstRows, dstCols);

  cv::warpAffine(self->mat, res, rotMatrix->mat, resSize);
  self->setMat(res);

  return;
}

NAN_METHOD(Matrix::PyrDown) {
  SETUP_FUNCTION(Matrix)

  int oldSize = self->mat.dataend - self->mat.datastart;
  cv::pyrDown(self->mat, self->mat);
  int newSize = self->mat.dataend - self->mat.datastart;
  Nan::AdjustExternalMemory(newSize - oldSize);
  return;
}

NAN_METHOD(Matrix::PyrUp) {
  SETUP_FUNCTION(Matrix)

  int oldSize = self->mat.dataend - self->mat.datastart;
  cv::pyrUp(self->mat, self->mat);
  int newSize = self->mat.dataend - self->mat.datastart;
  Nan::AdjustExternalMemory(newSize - oldSize);
  return;
}

NAN_METHOD(Matrix::inRange) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  /*if (self->mat.channels() != 3)
   Nan::ThrowError(String::New("Image is no 3-channel"));*/

  if (info[0]->IsArray() && info[1]->IsArray()) {
    Local<Object> args_lowerb = Nan::To<v8::Object>(info[0]).ToLocalChecked();
    Local<Object> args_upperb = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

    cv::Scalar lowerb(0, 0, 0);
    cv::Scalar upperb(0, 0, 0);

    lowerb = setColor(args_lowerb);
    upperb = setColor(args_upperb);

    cv::Mat mask;
    cv::inRange(self->mat, lowerb, upperb, mask);
    mask.copyTo(self->mat);
  }

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::AdjustROI) {
  SETUP_FUNCTION(Matrix)
  int dtop = info[0]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int dbottom = info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int dleft = info[2]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  int dright = info[3]->Uint32Value(Nan::GetCurrentContext()).ToChecked();

  self->mat.adjustROI(dtop, dbottom, dleft, dright);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::LocateROI) {
  SETUP_FUNCTION(Matrix)

  cv::Size wholeSize;
  cv::Point ofs;

  self->mat.locateROI(wholeSize, ofs);

  v8::Local < v8::Array > arr = Nan::New<Array>(4);
   Nan::Set(arr, 0, Nan::New<Number>(wholeSize.width));
   Nan::Set(arr, 1, Nan::New<Number>(wholeSize.height));
   Nan::Set(arr, 2, Nan::New<Number>(ofs.x));
   Nan::Set(arr, 3, Nan::New<Number>(ofs.y));

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Matrix::Threshold) {
  SETUP_FUNCTION(Matrix)

  double threshold = info[0].As<Number>()->Value();
  double maxVal = info[1].As<Number>()->Value();
  int typ = cv::THRESH_BINARY;

  if (info.Length() >= 3) {
    Nan::Utf8String typstr(info[2]);

    if (strcmp(*typstr, "Binary") == 0) {
      // Uses default value
    }
    else if (strcmp(*typstr, "Binary Inverted") == 0) {
      typ = cv::THRESH_BINARY_INV;
    }
    else if (strcmp(*typstr, "Threshold Truncated") == 0) {
      typ = cv::THRESH_TRUNC;
    }
    else if (strcmp(*typstr, "Threshold to Zero") == 0) {
      typ = cv::THRESH_TOZERO;
    }
    else if (strcmp(*typstr, "Threshold to Zero Inverted") == 0) {
      typ = cv::THRESH_TOZERO_INV;
    }
    else {
      char *typeString = *typstr;
      char text[] = "\" is no supported binarization technique. "
        "Use \"Binary\" (default), \"Binary Inverted\", "
        "\"Threshold Truncated\", \"Threshold to Zero\" "
        "or \"Threshold to Zero Inverted\"";
      char *errorMessage;
      errorMessage = new char[strlen(typeString) + strlen(text) + 2];
      strcpy(errorMessage, "\"");
      strcat(errorMessage, typeString);
      strcat(errorMessage, text);

      Nan::ThrowError(errorMessage);
      return;
    }
  }

  if (info.Length() >= 4) {
    Nan::Utf8String algorithm(info[3]);

    if (strcmp(*algorithm, "Simple") == 0) {
        // Uses default
    }
    else if (strcmp(*algorithm, "Otsu") == 0) {
      typ += 8;
    }
    else {
      char *algo = *algorithm;
      char text[] = "\" is no supported threshold algorithm. "
        "Use \"Simple\" (default) or \"Otsu\".";
      char *errorMessage;
      errorMessage = new char[strlen(algo) + strlen(text) + 2];
      strcpy(errorMessage, "\"");
      strcat(errorMessage, algo);
      strcat(errorMessage, text);

      Nan::ThrowError(errorMessage);
      return;
    }
  }

  cv::Mat outputmat = cv::Mat();
  self->mat.copyTo(outputmat);

  cv::threshold(self->mat, outputmat, threshold, maxVal, typ);

  Local < Object > img_to_return = CreateWrappedFromMat(outputmat);

  info.GetReturnValue().Set(img_to_return);
}

NAN_METHOD(Matrix::AdaptiveThreshold) {
  SETUP_FUNCTION(Matrix)

  double maxVal = info[0].As<Number>()->Value();
  double adaptiveMethod = info[1].As<Number>()->Value();
  double thresholdType = info[2].As<Number>()->Value();
  double blockSize = info[3].As<Number>()->Value();
  double C = info[4].As<Number>()->Value();

  cv::Mat outputmat = cv::Mat();
  self->mat.copyTo(outputmat);

  cv::adaptiveThreshold(self->mat, outputmat, maxVal, adaptiveMethod,
      thresholdType, blockSize, C);
  
  Local < Object > img_to_return = CreateWrappedFromMat(outputmat);

  info.GetReturnValue().Set(img_to_return);
}

NAN_METHOD(Matrix::MeanStdDev) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  cv::Mat meanMat = cv::Mat();
  cv::Mat stddevMat = cv::Mat();

  cv::meanStdDev(self->mat, meanMat, stddevMat);

  Local<Object> data = Nan::New<Object>();
  Nan::Set(data,Nan::New<String>("mean").ToLocalChecked(), CreateWrappedFromMat(meanMat));
  Nan::Set(data,Nan::New<String>("stddev").ToLocalChecked(), CreateWrappedFromMat(stddevMat));

  info.GetReturnValue().Set(data);
}

// @author SergeMv
// Copies our (small) image into a ROI of another (big) image
// @param Object another image (destination)
// @param Number Destination x (where our image is to be copied)
// @param Number Destination y (where our image is to be copied)
// Example: smallImg.copyTo(bigImg, 50, 50);
// Note, x,y and width and height of our image must be so that
// our.width + x <= destination.width (and the same for y and height)
// both x and y must be >= 0
NAN_METHOD(Matrix::CopyTo) {
  Nan::HandleScope scope;

  Matrix * self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  int width = self->mat.size().width;
  int height = self->mat.size().height;

  // param 0 - destination image:
  Matrix *dest = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  // param 1 - x coord of the destination
  int x = Nan::To<int>(info[1]).FromJust();
  // param 2 - y coord of the destination
  int y = info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

  cv::Mat dstROI = cv::Mat(dest->mat, cv::Rect(x, y, width, height));
  self->mat.copyTo(dstROI);

  return;
}

/**
 * Converts an array to another data type with optional scaling
 * Reference: http://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat-convertto
 */
NAN_METHOD(Matrix::ConvertTo) {
  SETUP_FUNCTION(Matrix)

  if (info.Length() < 2) {
    JSTHROW("Invalid number of arguments");
  }

  // param 0 - destination image
  Matrix *dest = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  // param 1 - desired matrix type
  int rtype = -1;
  INT_FROM_ARGS(rtype, 1);

  // param 2 - alpha
  double alpha = 1;
  if (info.Length() >= 3) {
    DOUBLE_FROM_ARGS(alpha, 2);
  }

  // param 3 - beta
  double beta = 0;
  if (info.Length() >= 4) {
    DOUBLE_FROM_ARGS(beta, 3);
  }

  self->mat.convertTo(dest->mat, rtype, alpha, beta);

  return;
}

// @author SergeMv
// Does in-place color transformation
// img.cvtColor('CV_BGR2YCrCb');
NAN_METHOD(Matrix::CvtColor) {
  Nan::HandleScope scope;

  Matrix * self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  if (info.Length() < 1) {
    Nan::ThrowTypeError("Invalid number of arguments");
  }

  // Get transform string
  v8::String::Utf8Value str (v8::Isolate::GetCurrent(),info[0]->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>()));
  std::string str2 = std::string(*str);
  const char * sTransform = (const char *) str2.c_str();
  int iTransform;

  if (!strcmp(sTransform, "CV_BGR2GRAY")) {
    iTransform = CV_BGR2GRAY;
  } else if (!strcmp(sTransform, "CV_GRAY2BGR")) {
    iTransform = CV_GRAY2BGR;
  } else if (!strcmp(sTransform, "CV_BGR2XYZ")) {
    iTransform = CV_BGR2XYZ;
  } else if (!strcmp(sTransform, "CV_XYZ2BGR")) {
    iTransform = CV_XYZ2BGR;
  } else if (!strcmp(sTransform, "CV_BGR2YCrCb")) {
    iTransform = CV_BGR2YCrCb;
  } else if (!strcmp(sTransform, "CV_YCrCb2BGR")) {
    iTransform = CV_YCrCb2BGR;
  } else if (!strcmp(sTransform, "CV_BGR2HSV")) {
    iTransform = CV_BGR2HSV;
  } else if (!strcmp(sTransform, "CV_HSV2BGR")) {
    iTransform = CV_HSV2BGR;
  } else if (!strcmp(sTransform, "CV_BGR2HLS")) {
    iTransform = CV_BGR2HLS;
  } else if (!strcmp(sTransform, "CV_HLS2BGR")) {
    iTransform = CV_HLS2BGR;
  } else if (!strcmp(sTransform, "CV_BGR2Lab")) {
    iTransform = CV_BGR2Lab;
  } else if (!strcmp(sTransform, "CV_Lab2BGR")) {
    iTransform = CV_Lab2BGR;
  } else if (!strcmp(sTransform, "CV_BGR2Luv")) {
    iTransform = CV_BGR2Luv;
  } else if (!strcmp(sTransform, "CV_Luv2BGR")) {
    iTransform = CV_Luv2BGR;
  } else if (!strcmp(sTransform, "CV_BayerBG2BGR")) {
    iTransform = CV_BayerBG2BGR;
  } else if (!strcmp(sTransform, "CV_BayerGB2BGR")) {
    iTransform = CV_BayerGB2BGR;
  } else if (!strcmp(sTransform, "CV_BayerRG2BGR")) {
    iTransform = CV_BayerRG2BGR;
  } else if (!strcmp(sTransform, "CV_BayerGR2BGR")) {
    iTransform = CV_BayerGR2BGR;
  } else if (!strcmp(sTransform, "CV_BGR2RGB")) {
    iTransform = CV_BGR2RGB;
  } else if (!strcmp(sTransform, "CV_BGRA2BGR")) {
    iTransform = CV_BGRA2BGR;
  } else {
    iTransform = 0;  // to avoid compiler warning
    Nan::ThrowTypeError("Conversion code is unsupported");
  }

  int oldSize = self->mat.dataend - self->mat.datastart;
  cv::cvtColor(self->mat, self->mat, iTransform);
  int newSize = self->mat.dataend - self->mat.datastart;
  if(oldSize != newSize){
    Nan::AdjustExternalMemory(newSize - oldSize);
  }

  return;
}

// @author SergeMv
// arrChannels = img.split();
NAN_METHOD(Matrix::Split) {
  Nan::HandleScope scope;

  Matrix * self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  unsigned int size = self->mat.channels();
  std::vector<cv::Mat> channels;

  // Split doesn't seem to work on empty vectors
  for (unsigned int i = 0; i < size; i++) {
    channels.push_back(cv::Mat());
  }

  cv::split(self->mat, channels);
  size = channels.size();
  v8::Local<v8::Array> arrChannels = Nan::New<Array>(size);
  for (unsigned int i = 0; i < size; i++) {
    Local<Object> matObject = Matrix::CreateWrappedFromMatIfNotReferenced(channels[i], 1);
    Nan::Set(arrChannels, i, matObject);
  }

  info.GetReturnValue().Set(arrChannels);
}

// @author SergeMv
// img.merge(arrChannels);
NAN_METHOD(Matrix::Merge) {
  Nan::HandleScope scope;

  Matrix * self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  if (!info[0]->IsArray()) {
    Nan::ThrowTypeError("The argument must be an array");
  }
  int oldSize = self->mat.dataend - self->mat.datastart;
  v8::Local<v8::Array> jsChannels = v8::Local<v8::Array>::Cast(info[0]);

  unsigned int L = jsChannels->Length();
  std::vector<cv::Mat> vChannels(L);
  for (unsigned int i = 0; i < L; i++) {
    Matrix * matObject = Nan::ObjectWrap::Unwrap<Matrix>( Nan::To<v8::Object>(  Nan::Get(jsChannels,i).ToLocalChecked() ).ToLocalChecked() );
    vChannels[i] = matObject->mat;
  }
  cv::merge(vChannels, self->mat);
  int newSize = self->mat.dataend - self->mat.datastart;
  Nan::AdjustExternalMemory(newSize - oldSize);

  return;
}

// @author SergeMv
// Equalizes histogram
// img.equalizeHist()
NAN_METHOD(Matrix::EqualizeHist) {
  Nan::HandleScope scope;
  Matrix * self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  cv::equalizeHist(self->mat, self->mat);

  return;
}

NAN_METHOD(Matrix::FloodFill) {
  SETUP_FUNCTION(Matrix)
  // obj->Get(Nan::GetCurrentContext(), Nan::New<String>("x").ToLocalChecked())
  // int cv::floodFill(cv::InputOutputArray, cv::Point, cv::Scalar, cv::Rect*, cv::Scalar, cv::Scalar, int)

  /*  mat.floodFill( {seedPoint: [1,1] ,
        newColor: [255,0,0] ,
        rect:[[0,2],[30,40]] ,
        loDiff : [8,90,60],
        upDiff:[10,100,70]
      }); */

  if (info.Length() < 1 || !info[0]->IsObject()) {
    // error
  }

  Local < Object > obj = Nan::To<v8::Object>(info[0]).ToLocalChecked();
  cv::Rect rect;

  int ret = cv::floodFill(self->mat,
      setPoint( Nan::To<v8::Object>( Nan::Get(obj,Nan::New<String>("seedPoint").ToLocalChecked()).ToLocalChecked() ).ToLocalChecked()),
      setColor( Nan::To<v8::Object>( Nan::Get(obj,Nan::New<String>("newColor").ToLocalChecked()).ToLocalChecked() ).ToLocalChecked()),
      Nan::Get(obj,Nan::New<String>("rect").ToLocalChecked()).IsEmpty() ?
          0 : setRect( Nan::To<Object>( Nan::Get(obj,Nan::New<String>("rect").ToLocalChecked()).ToLocalChecked() ).ToLocalChecked(), rect),
      setColor( Nan::To<v8::Object>( Nan::Get(obj,Nan::New<String>("loDiff").ToLocalChecked()).ToLocalChecked() ).ToLocalChecked()),
      setColor( Nan::To<v8::Object>( Nan::Get(obj,Nan::New<String>("upDiff").ToLocalChecked()).ToLocalChecked() ).ToLocalChecked()), 
      
      4);

  // Documentation notes that parameter "rect" is an optional output
  // parameter which will hold the smallest possible bounding box of
  // affected pixels. If "rect" was provided, let's update the values.
  // (https://docs.opencv.org/2.4/modules/imgproc/doc/miscellaneous_transformations.html#floodfill)
  if (! Nan::Get(obj,Nan::New<String>("rect").ToLocalChecked()).IsEmpty()) {
    Local< Object > rectArgument = Nan::To<v8::Object>( Nan::Get(obj,Nan::New<String>("rect").ToLocalChecked()).ToLocalChecked() ).ToLocalChecked();
    //obj->Get(Nan::GetCurrentContext(), Nan::New<String>("rect").ToLocalChecked())->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

    
    //Nan::Get(rectArgument,0)->ToObject(Nan::GetCurrentContext()).ToLocalChecked()->Set(Nan::GetCurrentContext(),0, Nan::New<Number>(rect.x));
     Nan::Set( Nan::To<v8::Object>( Nan::Get(rectArgument,0).ToLocalChecked() ).ToLocalChecked(), 0, Nan::New<Number>(rect.x) );
    //Nan::Get(rectArgument,0)->ToObject(Nan::GetCurrentContext()).ToLocalChecked()->Set(Nan::GetCurrentContext(),1, Nan::New<Number>(rect.y));
     Nan::Set( Nan::To<v8::Object>( Nan::Get(rectArgument,0).ToLocalChecked() ).ToLocalChecked(), 1, Nan::New<Number>(rect.y) );
    //Nan::Get(rectArgument,1)->ToObject(Nan::GetCurrentContext()).ToLocalChecked()->Set(Nan::GetCurrentContext(),0, Nan::New<Number>(rect.width));
     Nan::Set( Nan::To<v8::Object>( Nan::Get(rectArgument,1).ToLocalChecked() ).ToLocalChecked(), 0, Nan::New<Number>(rect.width) );
    //Nan::Get(rectArgument,1)->ToObject(Nan::GetCurrentContext()).ToLocalChecked()->Set(Nan::GetCurrentContext(),1, Nan::New<Number>(rect.height));
     Nan::Set( Nan::To<v8::Object>( Nan::Get(rectArgument,1).ToLocalChecked() ).ToLocalChecked(), 1, Nan::New<Number>(rect.height) );
  }

  info.GetReturnValue().Set(Nan::New<Number>(ret));
}

// @author olfox
// Returns an array of the most probable positions
// Usage: output = input.templateMatches(min_probability, max_probability, limit, ascending, min_x_distance, min_y_distance);
NAN_METHOD(Matrix::TemplateMatches) {
  SETUP_FUNCTION(Matrix)

  bool filter_min_probability =
      (info.Length() >= 1) ? info[0]->IsNumber() : false;
  bool filter_max_probability =
      (info.Length() >= 2) ? info[1]->IsNumber() : false;
  double min_probability = filter_min_probability ? info[0].As<Number>()->Value() : 0;
  double max_probability = filter_max_probability ? info[1].As<Number>()->Value() : 0;
  int limit = (info.Length() >= 3) ? info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : 0;
  bool ascending = (info.Length() >= 4) ? Nan::To<bool>(info[3] ).FromJust() : false;
  int min_x_distance = (info.Length() >= 5) ? info[4]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : 0;
  int min_y_distance = (info.Length() >= 6) ? info[5]->IntegerValue( Nan::GetCurrentContext() ).ToChecked() : 0;

  cv::Mat_<int> indices;

  if (ascending) {
    cv::sortIdx(self->mat.reshape(0, 1), indices,
    CV_SORT_ASCENDING + CV_SORT_EVERY_ROW);
  } else {
    cv::sortIdx(self->mat.reshape(0, 1), indices,
    CV_SORT_DESCENDING + CV_SORT_EVERY_ROW);
  }

  cv::Mat hit_mask = cv::Mat::zeros(self->mat.size(), CV_64F);
  v8::Local < v8::Array > probabilites_array = Nan::New<v8::Array>(limit);

  cv::Mat_<float>::const_iterator begin = self->mat.begin<float>();
  cv::Mat_<int>::const_iterator it = indices.begin();
  cv::Mat_<int>::const_iterator end = indices.end();
  int index = 0;

  for (; (limit == 0 || index < limit) && it != end; ++it) {
    cv::Point pt = (begin + *it).pos();

    float probability = self->mat.at<float>(pt.y, pt.x);

    if (filter_min_probability && probability < min_probability) {
      if (ascending) {
        continue;
      }
      else {
        break;
      }
    }

    if (filter_max_probability && probability > max_probability) {
      if (ascending)
        break;
      else
        continue;
    }

    if (min_x_distance != 0 || min_y_distance != 0) {
      // Check hit mask color for for every corner

      cv::Size maxSize = hit_mask.size();
      int max_x = maxSize.width - 1;
      int max_y = maxSize.height - 1;
      cv::Point top_left = cv::Point(std::max(0, pt.x - min_x_distance),
        std::max(0, pt.y - min_y_distance));
      cv::Point top_right = cv::Point(std::min(max_x, pt.x + min_x_distance),
        std::max(0, pt.y - min_y_distance));
      cv::Point bottom_left = cv::Point(std::max(0, pt.x - min_x_distance),
        std::min(max_y, pt.y + min_y_distance));
      cv::Point bottom_right = cv::Point(std::min(max_x, pt.x + min_x_distance),
        std::min(max_y, pt.y + min_y_distance));
      if (hit_mask.at<double>(top_left.y, top_left.x) > 0)
        continue;
      if (hit_mask.at<double>(top_right.y, top_right.x) > 0)
        continue;
      if (hit_mask.at<double>(bottom_left.y, bottom_left.x) > 0)
        continue;
      if (hit_mask.at<double>(bottom_right.y, bottom_right.x) > 0)
        continue;
      cv::Scalar color(255.0);
      cv::rectangle(hit_mask, top_left, bottom_right, color, CV_FILLED);
    }

    Local<Value> x_value = Nan::New<Number>(pt.x);
    Local<Value> y_value = Nan::New<Number>(pt.y);
    Local<Value> probability_value = Nan::New<Number>(probability);

    Local < Object > probability_object = Nan::New<Object>();
    Nan::Set(probability_object,Nan::New<String>("x").ToLocalChecked(), x_value);
    Nan::Set(probability_object,Nan::New<String>("y").ToLocalChecked(), y_value);
    Nan::Set(probability_object,Nan::New<String>("probability").ToLocalChecked(), probability_value);

    Nan::Set(probabilites_array,index, probability_object);
    index++;
  }

  info.GetReturnValue().Set(probabilites_array);
}

// @author Evilcat325
// MatchTemplate accept a Matrix
// Usage: output = input.matchTemplateByMatrix(matrix. method);
NAN_METHOD(Matrix::MatchTemplateByMatrix) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Matrix *templ = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  int cols = self->mat.cols - templ->mat.cols + 1;
  int rows = self->mat.rows - templ->mat.rows + 1;
  cv::Mat result(cols, rows, CV_32FC1);

  /*
   TM_SQDIFF        =0
   TM_SQDIFF_NORMED =1
   TM_CCORR         =2
   TM_CCORR_NORMED  =3
   TM_CCOEFF        =4
   TM_CCOEFF_NORMED =5
   */

  int method = (info.Length() < 2) ? (int)cv::TM_CCORR_NORMED : info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  if (!(method >= 0 && method <= 5)) method = (int)cv::TM_CCORR_NORMED;
  cv::matchTemplate(self->mat, templ->mat, result, method);
  info.GetReturnValue().Set(CreateWrappedFromMat(result));
}

// @author ytham
// Match Template filter
// Usage: output = input.matchTemplate("templateFileString", method);
NAN_METHOD(Matrix::MatchTemplate) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  v8::String::Utf8Value args0(v8::Isolate::GetCurrent(), info[0]->ToString(Nan::GetCurrentContext()).FromMaybe(v8::Local<v8::String>()));
  std::string filename = std::string(*args0);
  cv::Mat templ;
  templ = cv::imread(filename, -1);

  int cols = self->mat.cols - templ.cols + 1;
  int rows = self->mat.rows - templ.rows + 1;
  cv::Mat result(cols, rows, CV_32FC1);

  /*
   TM_SQDIFF        =0
   TM_SQDIFF_NORMED =1
   TM_CCORR         =2
   TM_CCORR_NORMED  =3
   TM_CCOEFF        =4
   TM_CCOEFF_NORMED =5
   */

  int method = (info.Length() < 2) ? (int)cv::TM_CCORR_NORMED : info[1]->Uint32Value(Nan::GetCurrentContext()).ToChecked();
  cv::matchTemplate(self->mat, templ, result, method);
  cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
  double minVal;
  double maxVal;
  cv::Point minLoc;
  cv::Point maxLoc;
  cv::Point matchLoc;

  minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

  if(method  == CV_TM_SQDIFF || method == CV_TM_SQDIFF_NORMED) {
    matchLoc = minLoc;
  }
  else {
    matchLoc = maxLoc;
  }

  //detected ROI
  unsigned int roi_x = matchLoc.x;
  unsigned int roi_y = matchLoc.y;
  unsigned int roi_width = templ.cols;
  unsigned int roi_height = templ.rows;

  //draw rectangle
  if(info.Length() >= 3) {
    cv::Rect roi(roi_x,roi_y,roi_width,roi_height);
    cv::rectangle(self->mat, roi, cv::Scalar(0,0,255));
  }

  result.convertTo(result, CV_8UC1, 255, 0);

  v8::Local <v8::Array> arr = Nan::New<v8::Array>(5);
   Nan::Set(arr, 0, CreateWrappedFromMat(result));
   Nan::Set(arr, 1, Nan::New<Number>(roi_x));
   Nan::Set(arr, 2, Nan::New<Number>(roi_y));
   Nan::Set(arr, 3, Nan::New<Number>(roi_width));
   Nan::Set(arr, 4, Nan::New<Number>(roi_height));

  info.GetReturnValue().Set(arr);
}

// @author ytham
// Min/Max location
NAN_METHOD(Matrix::MinMaxLoc) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
  cv::minMaxLoc(self->mat, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );

  Local<Value> v_minVal = Nan::New<Number>(minVal);
  Local<Value> v_maxVal = Nan::New<Number>(maxVal);
  Local<Value> v_minLoc_x = Nan::New<Number>(minLoc.x);
  Local<Value> v_minLoc_y = Nan::New<Number>(minLoc.y);
  Local<Value> v_maxLoc_x = Nan::New<Number>(maxLoc.x);
  Local<Value> v_maxLoc_y = Nan::New<Number>(maxLoc.y);

  Local<Object> o_minLoc = Nan::New<Object>();
  Nan::Set(o_minLoc,Nan::New<String>("x").ToLocalChecked(), v_minLoc_x);
  Nan::Set(o_minLoc,Nan::New<String>("y").ToLocalChecked(), v_minLoc_y);

  Local<Object> o_maxLoc = Nan::New<Object>();
  Nan::Set(o_maxLoc,Nan::New<String>("x").ToLocalChecked(), v_maxLoc_x);
  Nan::Set(o_maxLoc,Nan::New<String>("y").ToLocalChecked(), v_maxLoc_y);

  // Output result object
  Local<Object> result = Nan::New<Object>();
  Nan::Set(result,Nan::New<String>("minVal").ToLocalChecked(), v_minVal);
  Nan::Set(result,Nan::New<String>("maxVal").ToLocalChecked(), v_maxVal);
  Nan::Set(result,Nan::New<String>("minLoc").ToLocalChecked(), o_minLoc);
  Nan::Set(result, Nan::New<String>("maxLoc").ToLocalChecked(), o_maxLoc);

  info.GetReturnValue().Set(result);
}

// @author ytham
// Pushes some matrix (argument) the back of a matrix (self)
NAN_METHOD(Matrix::PushBack) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Matrix *m_input = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  self->mat.push_back(m_input->mat);

  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(Matrix::PutText) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  Nan::Utf8String textString(info[0]);  //FIXME: might cause issues, see here https://github.com/rvagg/nan/pull/152
  char *text = *textString;//(char *) malloc(textString.length() + 1);
  //strcpy(text, *textString);

  int x = Nan::To<int>(info[1]).FromJust();
  int y = info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

  Nan::Utf8String fontString(info[3]);
  char *font = *fontString;//(char *) malloc(fontString.length() + 1);
  //strcpy(font, *fontString);
  int constFont = cv::FONT_HERSHEY_SIMPLEX;

  if (!strcmp(font, "HERSEY_SIMPLEX")) {constFont = cv::FONT_HERSHEY_SIMPLEX;}
  else if (!strcmp(font, "HERSEY_PLAIN")) {constFont = cv::FONT_HERSHEY_PLAIN;}
  else if (!strcmp(font, "HERSEY_DUPLEX")) {constFont = cv::FONT_HERSHEY_DUPLEX;}
  else if (!strcmp(font, "HERSEY_COMPLEX")) {constFont = cv::FONT_HERSHEY_COMPLEX;}
  else if (!strcmp(font, "HERSEY_TRIPLEX")) {constFont = cv::FONT_HERSHEY_TRIPLEX;}
  else if (!strcmp(font, "HERSEY_COMPLEX_SMALL")) {constFont = cv::FONT_HERSHEY_COMPLEX_SMALL;}
  else if (!strcmp(font, "HERSEY_SCRIPT_SIMPLEX")) {constFont = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;}
  else if (!strcmp(font, "HERSEY_SCRIPT_COMPLEX")) {constFont = cv::FONT_HERSHEY_SCRIPT_COMPLEX;}
  else if (!strcmp(font, "HERSEY_SCRIPT_SIMPLEX")) {constFont = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;}

  cv::Scalar color(0, 0, 255);

  if (info[4]->IsArray()) {
    Local<Object> objColor = info[4]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    color = setColor(objColor);
  }

  double scale = info.Length() < 6 ? 1 : info[5].As<Number>()->Value();
  double thickness = info.Length() < 7 ? 1 : info[6].As<Number>()->Value();

  cv::putText(self->mat, text, cv::Point(x, y), constFont, scale, color, thickness);

  return;
}

NAN_METHOD(Matrix::GetPerspectiveTransform) {
  Nan::HandleScope scope;

  // extract quad info
  Local<Object> srcArray = Nan::To<v8::Object>(info[0]).ToLocalChecked();
  Local<Object> tgtArray = info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();

  std::vector<cv::Point2f> src_corners(4);
  std::vector<cv::Point2f> tgt_corners(4);
  for (unsigned int i = 0; i < 4; i++) {
    src_corners[i] = cvPoint(Nan::To<int32_t>( Nan::Get(srcArray,i*2).ToLocalChecked()).FromJust(), Nan::To<int32_t>( Nan::Get(srcArray,i*2+1).ToLocalChecked()).FromJust());
    tgt_corners[i] = cvPoint(Nan::To<int32_t>( Nan::Get(tgtArray,i*2).ToLocalChecked()).FromJust(), Nan::To<int32_t>( Nan::Get(tgtArray,i*2+1).ToLocalChecked()).FromJust());
  }
 
  Local<Object> xfrm = Matrix::CreateWrappedFromMat(cv::getPerspectiveTransform(src_corners, tgt_corners));

  info.GetReturnValue().Set(xfrm);
}

NAN_METHOD(Matrix::WarpPerspective) {
  SETUP_FUNCTION(Matrix)

  Matrix *xfrm = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  int width = Nan::To<int>(info[1]).FromJust();
  int height = info[2]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();

  int flags = cv::INTER_LINEAR;
  int borderMode = cv::BORDER_REPLICATE;

  cv::Scalar borderColor(0, 0, 255);

  if (info[3]->IsArray()) {
    Local < Object > objColor = info[3]->ToObject(Nan::GetCurrentContext()).ToLocalChecked();
    borderColor = setColor(objColor);
  }

  cv::Mat res = cv::Mat(width, height, CV_32FC3);

  cv::warpPerspective(self->mat, res, xfrm->mat, cv::Size(width, height), flags,
      borderMode, borderColor);

  self->setMat(res);

  info.GetReturnValue().Set(Nan::Null());
}

NAN_METHOD(Matrix::CopyWithMask) {
  SETUP_FUNCTION(Matrix)

  // param 0 - destination image:
  Matrix *dest = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());
  // param 1 - mask. same size as src and dest
  Matrix *mask = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());

  self->mat.copyTo(dest->mat, mask->mat);

  return;
}

NAN_METHOD(Matrix::SetWithMask) {
  SETUP_FUNCTION(Matrix)

  // param 0 - target value:
  Local < Object > valArray = Nan::To<v8::Object>(info[0]).ToLocalChecked();
  cv::Scalar newvals;
  newvals.val[0] = Nan::To<double>( Nan::Get(valArray,0).ToLocalChecked()).FromJust() ;
  newvals.val[1] = Nan::To<double>( Nan::Get(valArray,1).ToLocalChecked()).FromJust() ;
  newvals.val[2] = Nan::To<double>( Nan::Get(valArray,2).ToLocalChecked()).FromJust() ;
  // param 1 - mask. same size as src and dest
  Matrix *mask = Nan::ObjectWrap::Unwrap<Matrix>(info[1]->ToObject(Nan::GetCurrentContext()).ToLocalChecked());

  self->mat.setTo(newvals, mask->mat);

  return;
}

NAN_METHOD(Matrix::MeanWithMask) {
  SETUP_FUNCTION(Matrix)

  // param 0 - mask. same size as src and dest
  Matrix *mask = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  cv::Scalar means = cv::mean(self->mat, mask->mat);
  v8::Local < v8::Array > arr = Nan::New<Array>(4);
   Nan::Set(arr, 0, Nan::New<Number>(means[0]));
   Nan::Set(arr, 1, Nan::New<Number>(means[1]));
   Nan::Set(arr, 2, Nan::New<Number>(means[2]));
   Nan::Set(arr, 3, Nan::New<Number>(means[3]));

  info.GetReturnValue().Set(arr);
}

NAN_METHOD(Matrix::Mean) {
  SETUP_FUNCTION(Matrix)

  cv::Scalar means = cv::mean(self->mat);
  v8::Local<v8::Array> arr = Nan::New<Array>(4);
   Nan::Set(arr, 0, Nan::New<Number>(means[0]));
   Nan::Set(arr, 1, Nan::New<Number>(means[1]));
   Nan::Set(arr, 2, Nan::New<Number>(means[2]));
   Nan::Set(arr, 3, Nan::New<Number>(means[3]));

  info.GetReturnValue().Set(arr);
}

// http://docs.opencv.org/2.4/modules/imgproc/doc/filtering.html#copymakeborder
NAN_METHOD(Matrix::CopyMakeBorder) {
  SETUP_FUNCTION(Matrix)

  double t = info[0].As<Number>()->Value();
  double b = info[1].As<Number>()->Value();
  double l = info[2].As<Number>()->Value();
  double r = info[3].As<Number>()->Value();

  int borderType = cv::BORDER_DEFAULT;
  cv::Scalar value;
  if (info.Length() > 4) {
    borderType = info[4]->IntegerValue( Nan::GetCurrentContext() ).ToChecked();
    value = cv::Scalar(0, 0, 0, 0);
    if (borderType == cv::BORDER_CONSTANT) {
      if (!info[5]->IsArray()) {
        Nan::ThrowTypeError("The argument must be an array");
      }
      v8::Local<v8::Array> objColor = v8::Local<v8::Array>::Cast(info[5]);
      unsigned int length = objColor->Length();

      Local<Value> valB = Nan::Get(objColor,0).ToLocalChecked();
      Local<Value> valG = Nan::Get(objColor,1).ToLocalChecked();
      Local<Value> valR = Nan::Get(objColor,2).ToLocalChecked();

      if (length == 3) {
        value = cv::Scalar(
          valB->IntegerValue( Nan::GetCurrentContext() ).ToChecked(),
          valG->IntegerValue( Nan::GetCurrentContext() ).ToChecked(),
          valR->IntegerValue( Nan::GetCurrentContext() ).ToChecked() 
        );
      } else if (length == 4) {
        Local<Value> valA = Nan::Get(objColor,3).ToLocalChecked();

        value = cv::Scalar(
          Nan::To<int>(valB).FromJust(),
          Nan::To<int>(valG).FromJust(),
          Nan::To<int>(valR).FromJust(),
          //valA->IntegerValue( Nan::GetCurrentContext() ).ToChecked()
          Nan::To<int>(valA).FromJust()
        );
      } else {
        Nan::ThrowError("Fill must include 3 or 4 colors");
      }
    }
  }

  cv::Mat padded;
  cv::copyMakeBorder(self->mat, padded, t, b, l, r, borderType, value);

  ~self->mat;
  self->mat = padded;

  return;
}

NAN_METHOD(Matrix::Shift) {
  SETUP_FUNCTION(Matrix)

  cv::Mat res;

  double tx = info[0].As<Number>()->Value();
  double ty = info[1].As<Number>()->Value();

  // get the integer values of info
  cv::Point2i deltai(ceil(tx), ceil(ty));

  int fill = cv::BORDER_REPLICATE;
  cv::Scalar value = cv::Scalar(0, 0, 0, 0);

  // INTEGER SHIFT
  // first create a border around the parts of the Mat that will be exposed
  int t = 0, b = 0, l = 0, r = 0;
  if (deltai.x > 0) {
    l = deltai.x;
  }
  if (deltai.x < 0) {
    r = -deltai.x;
  }
  if (deltai.y > 0) {
    t = deltai.y;
  }
  if (deltai.y < 0) {
    b = -deltai.y;
  }
  cv::Mat padded;
  cv::copyMakeBorder(self->mat, padded, t, b, l, r, fill, value);

  // construct the region of interest around the new matrix
  cv::Rect roi = cv::Rect(std::max(-deltai.x, 0), std::max(-deltai.y, 0), 0, 0)
      + self->mat.size();
  res = padded(roi);

  self->setMat(res);

  return;
}

/**
 * Changes the shape and/or the number of channels of a 2D matrix without
 * copying the data.
 * Reference:http://docs.opencv.org/2.4/modules/core/doc/basic_structures.html#mat-reshape
 */
NAN_METHOD(Matrix::Reshape) {
  SETUP_FUNCTION(Matrix)

  int cn = 0;
  int rows = 0;
  if (info.Length() == 2) {
    INT_FROM_ARGS(cn, 0);
    INT_FROM_ARGS(rows, 1);
  } else if (info.Length() == 1) {
    INT_FROM_ARGS(cn, 0);
  } else {
    JSTHROW("Invalid number of arguments");
  }

  Local<Object> img_to_return = Matrix::CreateWrappedFromMatIfNotReferenced(self->mat.reshape(cn, rows),0);

  info.GetReturnValue().Set(img_to_return);
}

NAN_METHOD(Matrix::Release) {
  Nan::HandleScope scope;

  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());

  if(self->getWrappedRefCount() == 1){
    int size = self->mat.dataend - self->mat.datastart;
    Nan::AdjustExternalMemory(-1 * size);
  }

  self->mat.release();

  return;
}

// leave this out - can't see a way it could be useful to us, as release() always completely forgets the data
//NAN_METHOD(Matrix::Addref) {
//  Nan::HandleScope scope;
//
//  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
//  self->mat.addref();
//
//  return;
//}


int Matrix::getWrappedRefCount(){
    int refcount = -1;
#if CV_MAJOR_VERSION >= 3
    if (mat.u){
        refcount = mat.u->refcount;
    } else {
        refcount = -1; // indicates no reference ptr
    }
#else
    if (mat.refcount){
        refcount = *(mat.refcount);
    } else {
        refcount = -1; // indicates no reference ptr
    }
#endif 
    return refcount;
}

NAN_METHOD(Matrix::GetrefCount) {
  Nan::HandleScope scope;
  Matrix *self = Nan::ObjectWrap::Unwrap<Matrix>(info.This());
  
  int refcount = self->getWrappedRefCount();

  info.GetReturnValue().Set(Nan::New<Number>(refcount));
  return;
}


NAN_METHOD(Matrix::Subtract) {
  SETUP_FUNCTION(Matrix)

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Invalid number of arguments");
  }

  Matrix *other = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  self->mat -= other->mat;

  return;
}

NAN_METHOD(Matrix::Compare) {
  SETUP_FUNCTION(Matrix)

  if (info.Length() < 2) {
    Nan::ThrowTypeError("Invalid number of arguments");
  }
  Matrix *other = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  int cmpop = Nan::To<int>(info[1]).FromJust();

  int width = self->mat.size().width;
  int height = self->mat.size().height;

  cv::Mat res = cv::Mat(width, height, CV_8UC1);

  cv::compare(self->mat, other->mat, res, cmpop);
  Local<Object> out = Matrix::CreateWrappedFromMat(res);

  info.GetReturnValue().Set(out);
  return;
}
NAN_METHOD(Matrix::Mul) {
  SETUP_FUNCTION(Matrix)

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Invalid number of arguments");
  }

  Matrix *other = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  double scale = 1;
  if (info.Length() > 1) scale = info[1].As<Number>()->Value();

  cv::Mat res = self->mat.mul(other->mat, scale);

  Local<Object> out = Matrix::CreateWrappedFromMat(res);

  info.GetReturnValue().Set(out);
  return;
}

NAN_METHOD(Matrix::Div) {
  SETUP_FUNCTION(Matrix)

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Invalid number of arguments");
  }

  Matrix *other = Nan::ObjectWrap::Unwrap<Matrix>(Nan::To<v8::Object>(info[0]).ToLocalChecked());

  cv::divide(self->mat, other->mat, self->mat);

  return;
}

NAN_METHOD(Matrix::Pow) {
  SETUP_FUNCTION(Matrix)

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Invalid number of arguments");
  }

  double power = info[0].As<Number>()->Value();

  cv::pow(self->mat, power, self->mat);

  return;
}

