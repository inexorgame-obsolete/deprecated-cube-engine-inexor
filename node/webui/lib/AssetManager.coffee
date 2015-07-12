define ["jquery"], ($) ->
  # TODO: Use async define
  req = $.ajax
    dataType: "json"
    url: "/list-assets"
    async: false

  class AssetManager
    assets: req.responseJSON
    list: -> @assets

  new AssetManager
