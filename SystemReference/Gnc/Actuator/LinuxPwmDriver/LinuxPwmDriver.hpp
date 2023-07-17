// ======================================================================
// \title  LinuxPwmDriver.hpp
// \author fprime
// \brief  hpp file for LinuxPwmDriver component implementation class
// ======================================================================

#ifndef LinuxPwmDriver_HPP
#define LinuxPwmDriver_HPP

#include "Drv/LinuxPwmDriver/LinuxPwmDriverComponentAc.hpp"
#include <Os/File.hpp>

namespace Drv {

  class LinuxPwmDriver :
    public LinuxPwmDriverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object LinuxPwmDriver
      //!
      LinuxPwmDriver(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object LinuxPwmDriver
      //!
      ~LinuxPwmDriver();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Driver helper functions and variables used by the handlers 
      // ----------------------------------------------------------------------
  
      Os::File fd; 
      
      Os::File::Status setOneByte( const char* filePath, U8 writeValue );
      Os::File::Status setExport(); // export returns an error if ran twice in a row 
                                    // this is okay however, generally export should be set
                                    // because it creates the pwm0 file system 
                                    //  which all other driver functions write to.
      Os::File::Status setUnexport();
      Os::File::Status enable();
      Os::File::Status disable(); 


      Os::File::Status setBytes( const char * filePath, const char * inBuf, NATIVE_INT_TYPE inBufSize );
      Os::File::Status setPeriod( U32 inU32 );
      Os::File::Status setOnTime( U32 inU32 );
    

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for enableAndExport
      //!
      void enableAndExport_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const Drv::OneByteOps &operationType 
      );

      //! Handler implementation for periodAndCycle
      //!
      void periodAndCycle_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const Drv::MultiByteOps &operationType, 
          U32 operationValue 
      );

    };

} // end namespace Drv

#endif
