define(['./module'], function(controllers) {
  'use strict';
  controllers.controller('UiTestController', ['$scope',
    function ($scope) {

      $scope.myInterval = 5000;
      $scope.noWrapSlides = false;
      $scope.active = 0;
      $scope.slides = [];
      $scope.currIndex = 0;
      $scope.toggleButton = true;
      $scope.radioModel = 'Middle';
      $scope.checkModel = {
        left: false,
        middle: true,
        right: false
      };

      $scope.addSlide = function() {
	    var newWidth = 600 + $scope.slides.length + 1;
	    $scope.slides.push({
	      image: 'http://lorempixel.com/' + newWidth + '/300',
	      text: ['Nice image','Awesome photograph','That is so cool','I love that'][$scope.slides.length % 4],
	      id: $scope.currIndex++
	    });
	  };

	  $scope.randomize = function() {
	    var indexes = $scope.generateIndexesArray();
	    $scope.assignNewIndexesToSlides(indexes);
	  };

	  // Randomize logic below
	  $scope.assignNewIndexesToSlides = function(indexes) {
	    for (var i = 0, l = $scope.slides.length; i < l; i++) {
	      $scope.slides[i].id = indexes.pop();
	    }
	  };

	  $scope.generateIndexesArray = function() {
	    var indexes = [];
	    for (var i = 0; i < $scope.currIndex; ++i) {
	      indexes[i] = i;
	    }
	    return $scope.shuffle(indexes);
	  }

	  $scope.shuffle = function(array) {
	    var tmp, current, top = array.length;
	    if (top) {
	      while (--top) {
	        current = Math.floor(Math.random() * (top + 1));
	        tmp = array[current];
	        array[current] = array[top];
	        array[top] = tmp;
	      }
	    }
	    return array;
	  }

      for (var i = 0; i < 4; i++) {
        $scope.addSlide();
      }

      console.log("UiTestController initialized!");

    }
  ]);
});
