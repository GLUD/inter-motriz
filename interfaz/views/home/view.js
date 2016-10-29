'use strict';

angular.module('myApp.home', ['ngRoute'])

.config(['$routeProvider', function($routeProvider) {
    $routeProvider.when('/home', {
        templateUrl: 'views/home/view.html',
        controller: 'HomeCtrl'
    })
}])

.controller('HomeCtrl', [
    '$scope',
    '$http',
    '$location',
    function(
        $scope,
        $http,
        $location
    ) {
        $scope.estado = ''
        $scope.primero = true
        $scope.setEstado = function(estado) {
            $scope.estado = estado
            $scope.primero = false
        }
        $scope.dispositivo = ''
        $scope.setDispositivo = function(dispositivo) {
            $scope.dispositivo = dispositivo
            $http.get("http://localhost:12345/?param1=on&param2=off")
                .then(function(response) {
                    //First function handles success
                    $scope.content = response.data;
                }, function(response) {
                    //Second function handles error
                    $scope.content = "Something went wrong";
                });
            $scope.primero = true
        }
    }
])