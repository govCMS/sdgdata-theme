(function ($, Drupal, window, document, undefined) {

  /**
   * Turn a set of field items into tabs. Great for use with field collections or
   * entity references. It restructures the html to be compatible with a tab sructure
   * then applies easy responsive tabs.
   *
   * @param settings
   */
  $.fn.containersToTabs = function(settings) {

    // Don't act on processed element.
    if (this.hasClass('containers-to-tabs')) {
      return this;
    }

    // Default settings.
    var defaultSettings = {
      tabSelector: 'label',
      paneSelector: '.field-item',
      tabsSettings: {},
    };
    settings = $.extend(defaultSettings, settings);

    // Vars we will need.
    var tabClass = settings.tabSelector.substr(1),
      $tab = {},
      tabText = '';

    // This could be running on multiple elements and each needs
    // to be delt with individually.
    this.each(function(i, el){

      var $el = $(el),
        identifier = 'tab-set-' + i
      $panes = $el.find(settings.paneSelector),
        $tabs = $('<ul>', {class: 'resp-tabs-list ' + identifier});

      // Loop over each pane to build the tabs.
      $panes.each(function(i,pane){

        // Parse the current pane.
        var $pane = $(pane);

        // Get the tab text/id.
        tabText = $pane.find(settings.tabSelector).text();

        // Create the tab and add the data-id
        $tab = $('<li>', {class: tabClass});
        $tab.html(tabText).data('id', i);

        // Add the original tab classes.
        $tab.addClass($pane.find(settings.tabSelector).attr('class'));

        // Add the tabs and panes to the containers.
        $tabs.append($tab);

        // Remove the original tab selector from the mix.
        $pane.find(settings.tabSelector).remove();

      });

      // Wrap panes.
      $panes.wrapAll('<div class="resp-tabs-container ' + identifier + '" />');

      // Add the tabs to the parent.
      $el.prepend($tabs);

      // Mark as processed.
      $el.addClass('containers-to-tabs');

      // Finally, add tab functionality.
      settings.tabsSettings.tabidentify = identifier;
      $el.easyResponsiveTabs(settings.tabsSettings);

    });

    // Return for chaining.
    return this;

  };

  /**
   * Convert containers to tabs.
   */
  Drupal.behaviors.sdgContainersToTabs = {
    attach: function(context, settings) {
      $('#metadata').containersToTabs({
        tabSelector: '> h3', // Selector tab name.
        paneSelector: '.metadata__pane', // Selector pane content.
        // See https://github.com/samsono/Easy-Responsive-Tabs-to-Accordion
        tabsSettings: {
          type: 'default',
          fit: true,
          width: 'auto',
        }
      });
    }
  };

})(jQuery, Drupal, this, this.document);
