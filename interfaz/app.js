'use strict';

// Declare app level module which depends on views, and components
angular.module('myApp', [
    'mm.foundation',
    'ngRoute',
    'myApp.home'
])
.config([
    '$locationProvider',
    '$routeProvider',
    function(
        $locationProvider,
        $routeProvider
    ) {
        $locationProvider.hashPrefix('!')

        $routeProvider.otherwise({
            redirectTo: '/home'
        })
    }
])

//Please see https://www.consolelog.io/angularjs-change-path-without-reloading
