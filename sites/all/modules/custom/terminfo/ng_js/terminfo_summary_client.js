/**
 * file
 */
(function ($) {
  var basePathUrl = Drupal.settings.basePath;
  var currentUserUid = Drupal.settings.currentUserUid;

  /**
   * AngularJS
   */
  var app = angular.module('termClientIndex', ['ngMaterial']);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  app.factory("mainData", ['$http', function($http) {
    var jsonfile = basePathUrl + 'api/json/term/all-client-data';
    var obj = {};

    obj.fetchJsonDetails = function(){
      return $http.get(jsonfile);
    }

    return obj;
  }]);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  /**
   * term Client
   */
  app.controller('termClientController', ['$scope', '$http', 'mainData', function($scope, $http, mainData) {
    mainData.fetchJsonDetails().success(function(data) {
      $scope.sourcedata = data;
      // Do some thing handling here

      /**
       * iterator, add parameter on end of link
       */
      jQuery.each($scope.sourcedata, function(key, value) {
       value.linkAddUserClientManager += '/' + value.termTid + '/' + currentUserUid;
       value.linkRemoveUserClientManager += '/' + value.termTid + '/' + currentUserUid;
      });
    })
    .error(function (data, status, headers, config) {
       // Do some error handling here
    });

    /**
     * toggle status
     */
    $scope.clientToggleStatus = true;
    $scope.clientToggleStatusChange = function() {
      $scope.clientToggleStatus = !$scope.clientToggleStatus;
    }

    /**
     * my client status
     */
    $scope.currentClientStatus = function(clientManageUserArray) {
      if(jQuery.inArray(currentUserUid, clientManageUserArray) > -1){
        return false;
      }
      return true;
    }

    /**
     * my client status
     */
    $scope.myClientList = true;
    $scope.myClientList = function() {
      if(jQuery.inArray(currentUserUid, codes) > -1) {
        $scope.currentClientStatus = function(clientManageUserArray) {
          if(jQuery.inArray(currentUserUid, clientManageUserArray) > -1) {
            return true;
          }
          return false;
        }
      }
    }
  }]);

  /**
   * term Contact
   */
  app.controller('termContactController', ['$scope', '$http', function($scope, $http) {
    var jsonFilePath = basePathUrl + 'api/json/term/all-contact-data';

    $http.get(jsonFilePath)
      .success(function (data) {
         $scope.sourcedata = data;
         console.log($scope.sourcedata);
      })
      .error(function (data, status, headers, config) {
         // Do some error handling here
      });


  }]);

})(jQuery);
