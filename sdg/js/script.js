/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {

  /*
   * Menu mobile button.
   */
  Drupal.behaviors.menuMobileButton = {
    attach: function (context, settings) {

      // DOM elements.
      var $mobileMenu = $('.menu-toggle', context),
          $mainMenu = $('.block-menu', context),
          $dimState = $('.block-menu, .menu-toggle', context),
          menuOpenClass = 'mobile-menu-open';

      // Trigger mobile menu.
      $mobileMenu.click(function(){
        // Slide menu in.
        $mainMenu.slideToggle();

        // Add class that triggers mobile menu.
        $('body').toggleClass(menuOpenClass);

        // Add and remove dim state.
        if ($('body').hasClass(menuOpenClass)) {
          $dimState.dimBackground();
        } else {
          $dimState.undim();
        }

      });

    }
  };

  /*
   * Search form block.
   */
  Drupal.behaviors.sdgSearchFormBlock = {
    attach: function (context, settings) {
      var $body = $('body'),
          $container = $('.search-form', context),
          $toggle = $('.search-form__toggle', $container),
          $inputText = $('.search-form__widget', $container),
          toggleClass = 'search-form-open';

      // Handle clicks on the toggle.
      $toggle.once('search-form-block').click(function (e) {
        if (!$body.hasClass(toggleClass)) {
          e.preventDefault();
          e.stopPropagation();
          $inputText.focus();
        }
        $body.toggleClass(toggleClass);
      });

      // Handle clicks anywhere on the page.
      $('html', context).once('search-form-block').click(function(e) {
        if (!$(e.target).is('.search-form__widget', $container)) {
          $body.removeClass(toggleClass);
        }
      });

      // Handles pressing the escape key.
      $(document).keyup(function(e) {
        if (e.keyCode === 27) {
          $body.removeClass(toggleClass);
          $inputText.blur();
        }
      });
    }
  };

  /*
   * Search filters overlay buttons.
   */
  Drupal.behaviors.sdgSearchFiltersOverlayButton = {
    attach: function (context, settings) {
      var $body = $('body'),
          $container = $('[data-search-filters-container]'),
          $toggleBtn = $('[data-search-filters-toggle]', context),
          $closeBtn = $('[data-search-filters-close]', context),
          toggleClass = 'search-filters-open';

      $toggleBtn.once('search-filters-toggle').click(function () {
        $body.toggleClass(toggleClass);

        if ($body.hasClass(toggleClass)) {
          $container.dimBackground();
        }
        else {
          $container.undim();
        }
      });

      $closeBtn.once('search-filters-close').click(function () {
        $body.removeClass(toggleClass);
        $container.undim();
      });
    }
  };

  /*
   * Indicator status donut.
   */
  Drupal.behaviors.sdgIndicatorStatusDonut = {
    attach: function (context, settings) {

      // Ensure we have circleChart available.
      if (typeof $.fn.circleChart !== 'function') {
        return;
      }

      // This should map to indicator palette in settings/_colors.scss
      var colMap = ['#5CB85C', '#F1AD4D', '#E27774', '#999999'],
        baseStartAngle = 275,
        startAngle = baseStartAngle;

      // Once indicator status is in viewport.
      inView('.view-indicator-status-graph').once('enter', function () {

        // Create donut.
        $('.indicator-donut', context).once('indicator-donut').each(function (i, d) {
          var percent = parseInt($(this).data('value'));

          $(this).circleChart({
            color: colMap[i],
            value: $(this).data('value'),
            unit: 'percent',
            animate: true,
            text: $(this).parent().find('.indicator-donut__content').html(),
            size: 260,
            widthRatio: 0.1,
            startAngle: baseStartAngle
          });

          // Rotate the start point as we loop through.
          startAngle = baseStartAngle + Math.round(((percent / 100) * 360));

        }); // end once.

      }); // end inview.

    }
  };

  /*
   * Match legend height.
   */
  Drupal.behaviors.sdgMatchHeight = {
    attach: function (context, settings) {
      $('.indicator-status-teaser', context).once('match-height').matchHeight();
    }
  };

  /*
   * Scroll to href of link.
   */
  Drupal.behaviors.sdgScrollTo = {
    attach: function (context, settings) {
      $('.js-scroll-to', context).once('scroll-to').each(function(i, d){
        var $target = $($(this).attr('href'));
        if ($target.length) {
          $(this).click(function(e) {
            e.preventDefault();
            $('html, body').animate({
              scrollTop: $target.offset().top
            }, 1000);
          });
        }
      });
    }
  };

  /*
   * Turn an image into a background-image on its parent. Img el remains but
   * set to visibility: hidden to act as a hidden spacer and honor AR.
   */
  Drupal.behaviors.imgToBg = {
    attach: function(context, settings) {
      $('.js-img-to-bg', context)
        .once('img-to-bg')
        .each(function(i, d){
          $(this).imgToBg(this);
        });
    }
  };

  /*
   * jQuery plugin for ImgToBg.
   */
  $.fn.imgToBg = function() {
    var $img;
    $img = this.find('img').first();
    if ($img.length > 0) {
      $img.css('visibility', 'hidden');
      this.css('background-image', 'url("' + $img.attr('src') + '")');
    }
  };

  /*
   * Event listener for when a chart has fished being initialised.
   *
   * This adds a 'Download data' button using href from the file link. Due to
   * order of execution this cannot be inside a behaviour.
   */
  $(window).bind('tableCharts:init:dom', function(e) {
    var $parent = e.el.$actions.closest('.file-ckan'),
        $fileContainer = $parent.find('span.file'),
        $fileLink = $fileContainer.find('a');

    $fileContainer
      .addClass('element-hidden');

    $('<button>')
      .html(Drupal.t('Download data'))
      .addClass('table-chart--download')
      .appendTo(e.el.$actions)
      .click(function(e) {
        window.open($fileLink.attr('href'));
      });
  });

  /*
 * Attach datatables.js to ckan tables.
 */
  Drupal.behaviors.ckanDataTables = {
    attach: function (context, settings) {

      // Responsive DataTables.
      $('table.govcms-ckan-table', context)
        .once('ckan-datatables')
        .attr('width', '100%')
        .DataTable({
          responsive: true,
          order: [],
          language: {
            "search": "Table search:"
          },
          lengthMenu: [20, 50, 100],
          // Only enable tab index on thead th and pagination.
          tabIndex: -1,
          headerCallback: function(thead, data, start, end, display) {
            $('th', thead).attr('tabindex', 0);
          },
          drawCallback: function(settings) {
            $('.paginate_button', settings.nTableWrapper).attr('tabindex', 0);
          }
        });
    }
  };

})(jQuery, Drupal, this, this.document);
