# Attribute that allows you to open another window:
# ```<a guiopen="inx-example">foobar</>```
# You can also instruct this to replace the current window:
# ```<a guiopen="inx-example" replace>foobar</>```
defineComponent 'guiopen', class extends Component
  # Whether this will replace  the window it's placed in
  @boolAttrAcc "replace"

  # The name of the gui to open
  @attrAcc targ: "guiopen"

  # If this is used within a window manager, that one;
  # if used outside a window manager, the default WM
  wm: =>
    wme = @elem.parents("wm")
    if wme
      Component.componentFor wme.get 0
    else
      WM

  window: => Component.componentFor(@elem.parents("window").get(0))
  
  @on "click", ->
    @wm().open @targ
    @window().close() if @replace
