#ifndef ConditionDatabase_ConnectionPool_h
#define ConditionDatabase_ConnectionPool_h

#include <string>
#include <memory>
//
#include "CoralBase/MessageStream.h"

namespace edm {
  class ParameterSet;
}

namespace coral {
  class IConnectionServiceConfiguration;
}

namespace cond {
  class CoralServiceManager;
  class DbConnectionConfiguration;
}

namespace cond {

  namespace persistency {
    // 
    enum DbAuthenticationSystem { UndefinedAuthentication=0,CondDbKey, CoralXMLFile };

    class ConnectionPool {
    public:
      ConnectionPool();
      ~ConnectionPool();

      void setMessageVerbosity( coral::MsgLevel level );
      void setAuthenticationPath( const std::string& p );
      void setAuthenticationSystem( int authSysCode );
      void setLogging( bool flag );   
      bool isLoggingEnabled() const;
      void setParameters( const edm::ParameterSet& connectionPset );
      void configure();
      Session createSession( const std::string& connectionString, bool writeCapable=false );
      Session createReadOnlySession( const std::string& connectionString, const std::string& transactionId );
      
    private:
      void configure( coral::IConnectionServiceConfiguration& coralConfig);
      // to be removed after the transition
      void configure( cond::DbConnectionConfiguration& oraConfiguration );
    private:
      std::string m_authPath;
      int m_authSys = 0;
      coral::MsgLevel m_messageLevel = coral::Info;
      bool m_loggingEnabled = false;
      // this one has to be moved!
      cond::CoralServiceManager* m_pluginManager = 0; 
    };
  }
}

#endif

