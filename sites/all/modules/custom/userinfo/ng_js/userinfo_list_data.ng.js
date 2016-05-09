/**
 * file
 */
(function ($) {
  var basePathUrl = Drupal.settings.basePath;
  var currentUserUid = Drupal.settings.currentUserUid;

  /**
   * AngularJS
   */
  var app = angular.module('userListData', []);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  app.factory("mainData", ['$http', function($http) {
    var jsonfile = basePathUrl + 'api/json/user/all-user-data';
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
  app.controller('UserListController', ['$scope', '$http', 'mainData', function($scope, $http, mainData) {
    mainData.fetchJsonDetails().success(function(data) {
      $scope.sourcedata = data.users.profile;
      console.log(data);
      // Do some thing handling here
    })
    .error(function (data, status, headers, config) {
       // Do some error handling here
    });

  }]);



})(jQuery);
