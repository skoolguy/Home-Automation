module.exports = (function () {
 
    // Instance stores a reference to the Singleton
    var instance;
   
    function init() {
   
        // Singleton class
        var lightStatus = {
            RED_BULB : 0,
            YELLOW_BULB : 0
        };
   
        // function called from setStatus
        function setLight(color, status){
            if(color == "red"){
                lightStatus.RED_BULB = status;
            } else {
                lightStatus.YELLOW_BULB = status
            }
        } 
      
        
      return {
 
        //function to set the lights
        setStatus: function(newLightStatus, callback){
            setLight("red", newLightStatus.redLight);
            setLight("yellow", newLightStatus.yellowLight);
            callback(lightStatus);
        },

        //function to get the status of the lights
        getStatus: function(){
            return lightStatus;
        }
   
      };
    };
    
   
    return {
   
      // Get the Singleton instance if one exists
      // or create one if it doesn't
      getInstance: function () {
   
        if ( !instance ) {
          instance = init();
        }
   
        return instance;
      }
   
    };
   
  })();
   
  